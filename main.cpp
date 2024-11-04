#include <algorithm>
#include <cstddef>
#include <cstdio>
#include <filesystem>
#include <nfd.h>
#include <raylib.h>
#include <stdlib.h>
#include <string>
#include <taglib/fileref.h>
#include <taglib/tag.h>
#include <unordered_set>
#include <utility>
#include <vector>

const int WIDTH = 300;
const int HEIGHT = 110;

const Color BG_COLOR = Color{0x14, 0x14, 0x1b, 0xff};
const std::pair<Color, Color> PALETTE = {Color{0xb1, 0x93, 0xba, 0xff},
                                         Color{0x84, 0x66, 0x8e, 0xff}};

const std::unordered_set<std::string> SUPPORTED_TYPES = {
    ".mp3", ".ogg", ".wav", ".aac", ".flac", ".m4a"};

struct Track {
    std::string path;
    std::string title;
    std::string artist;
};

std::vector<Track> playlist;

std::string get_dirpath() {
    NFD_Init();
    std::string res = "";

    nfdu8char_t *outPath;
    nfdresult_t result = NFD_PickFolderN(&outPath, NULL);
    switch (result) {
    case NFD_OKAY: {
        res = outPath;
    } break;
    default:
        break;
    }
    return res;
}

std::string get_filepath() {
    NFD_Init();
    std::string res = "";

    nfdu8char_t *outPath;
    nfdu8filteritem_t filters[1] = {
        {"Audio file", "mp3, ogg, wav, aac, flac, m4a"}};
    nfdopendialogu8args_t args = {0};
    args.filterList = filters;
    args.filterCount = 1;
    nfdresult_t result = NFD_OpenDialogU8_With(&outPath, &args);
    switch (result) {
    case NFD_OKAY: {
        res = outPath;
    } break;
    default:
        break;
    }
    return res;
}

std::vector<std::string> split(std::string &str, int maxlen,
                               char delimiter = ' ') {
    int len = str.length();
    str = (str.length() > 75) ? str.substr(0, 75) + "..." : str;
    std::vector<std::string> result;
    int current = 0;
    while (current < str.length()) {
        int predicted = std::min(len - 1, current + maxlen - 1);
        while (str[predicted] != delimiter && predicted < len - 1 &&
               predicted > current) {
            predicted--;
        }
        if (predicted == current)
            predicted = current + maxlen - 1;
        result.push_back(str.substr(current, predicted - current + 1));
        current = predicted + 1;
    }
    return result;
}

template <typename T, typename Iter> bool in(T item, Iter iter) {
    return (iter.find(item) != iter.end());
}

bool is_filetype_supported(std::string path) {
    std::string ext = std::filesystem::path(path).extension().string();
    return in<std::string, std::unordered_set<std::string>>(ext,
                                                            SUPPORTED_TYPES);
}

Track get_track(std::string path) {
    Track result = Track{path, "", ""};

    TagLib::FileRef f(path.data());

    if (!f.isNull() && f.tag()) {
        TagLib::Tag *tag = f.tag();
        result.artist = tag->artist().toCString(true);
        result.title = tag->title().toCString(true);
    }

    return result;
}

void add_to_playlist_recursive(const std::filesystem::path &dir) {
    for (auto &entry : std::filesystem::directory_iterator(dir)) {
        if (std::filesystem::is_directory(entry.status())) {
            add_to_playlist_recursive(entry.path());
        } else {
            if (is_filetype_supported(entry.path().string())) {
                Track track = get_track(entry.path().string());
                playlist.push_back(track);
            }
        }
    }
}

void set_playlist() {
    std::string path = get_dirpath();
    add_to_playlist_recursive(std::filesystem::path(path));
}

int main() {
    bool is_loaded = false;
    double volume = 0.1;
    bool is_paused = false;

    InitWindow(WIDTH, HEIGHT, "ray");
    InitAudioDevice();
    Track track;

    // Before playlist is loaded
    std::string default_msg =
        "Please use O to load a playlist or A to add one track";
    std::vector<std::string> msg = split(default_msg, 20, ' ');
    while (!WindowShouldClose() && !is_loaded) {

        if (IsKeyPressed(KEY_A)) {
            std::string path = get_filepath();
            track = get_track(path);
            playlist.push_back(track);
            is_loaded = true;
        }

        if (IsKeyPressed(KEY_O)) {
            playlist.clear();
            set_playlist();

            is_loaded = true;
        }

        BeginDrawing();

        ClearBackground(BG_COLOR);
        int shift = 0;
        for (std::string t : msg) {
            DrawText(t.data(), 10, 10 + 20 * shift, 20, PALETTE.first);
            shift++;
        }

        EndDrawing();
    }

    int current_index = 0;
    int playlist_index = 0;

    track = playlist[current_index];
    std::vector<std::string> title = split(track.title, 20, ' ');
    std::vector<std::string> author = split(track.artist, 30, ' ');
    Music music;
    music = LoadMusicStream(track.path.data());

    SetMusicVolume(music, volume);
    PlayMusicStream(music);
    while (!WindowShouldClose()) {
        if (playlist_index == current_index && IsMusicStreamPlaying(music)) {
            UpdateMusicStream(music);
        } else {
            if (playlist_index == current_index) {
                playlist_index = (playlist_index + 1 < playlist.size())
                                     ? playlist_index + 1
                                     : 0;
                UnloadMusicStream(music);
            }
            current_index = playlist_index;
            track = playlist[current_index];
            title = split(track.title, 20, ' ');
            author = split(track.artist, 30, ' ');

            music = LoadMusicStream(track.path.data());
            SetMusicVolume(music, volume);
            PlayMusicStream(music);
        }

        if (IsKeyPressed(KEY_A)) {
            std::string path = get_filepath();
            track = get_track(path);
            playlist.push_back(track);
        }

        if (IsKeyPressed(KEY_O)) {
            playlist.clear();
            current_index = 0;
            set_playlist();
        }

        if (IsKeyPressed(KEY_RIGHT)) {
            playlist_index =
                (playlist_index + 1 < playlist.size()) ? playlist_index + 1 : 0;
        }

        if (IsKeyPressed(KEY_LEFT)) {
            playlist_index = (playlist_index - 1 >= 0) ? playlist_index - 1
                                                       : playlist.size() - 1;
        }

        if (IsKeyPressed(KEY_SPACE)) {
            is_paused = !is_paused;
            if (is_paused)
                PauseMusicStream(music);
            else
                ResumeMusicStream(music);
        }

        if (IsKeyPressed(KEY_UP)) {
            volume = std::min(volume + 0.025, 0.5);
            SetMusicVolume(music, volume);
        } else if (IsKeyPressed(KEY_DOWN)) {
            volume = std::max(volume - 0.025, 0.025);
            SetMusicVolume(music, volume);
        }

        BeginDrawing();
        ClearBackground(BG_COLOR);

        // track title line
        int title_shift = 0;
        for (std::string line : title) {
            DrawText(line.data(), 10, 10 + 20 * title_shift, 20,
                     (!is_paused) ? PALETTE.first : LIGHTGRAY);
            title_shift++;
        }

        // author line
        int author_shift = 0;
        for (std::string line : author) {
            DrawText(line.data(), 10, 10 + 20 * title_shift + 10 * author_shift,
                     10, (!is_paused) ? PALETTE.second : GRAY);
            author_shift++;
        }

        // volume slider
        const double MAXH = 40.0;
        int h = MAXH * volume * 2;
        int pos_y = HEIGHT - 10 - h;
        const int MAXW = 15;
        int pos_x = WIDTH - 10 - MAXW;
        // volume slider background
        DrawRectangle(pos_x, HEIGHT - 10 - MAXH, MAXW, MAXH,
                      (!is_paused) ? PALETTE.second : GRAY);
        // slider itself
        DrawRectangle(pos_x, pos_y, MAXW, h,
                      (!is_paused) ? PALETTE.first : LIGHTGRAY);

        EndDrawing();
    }

    UnloadMusicStream(music);
    CloseAudioDevice();
    CloseWindow();

    return 0;
}
