#include <algorithm>
#include <cstdio>
#include <nfd.h>
#include <queue>
#include <raylib.h>
#include <stdlib.h>
#include <string>
#include <taglib/fileref.h>
#include <taglib/tag.h>
#include <utility>
#include <vector>

const int WIDTH = 300;
const int HEIGHT = 110;

const Color BG_COLOR = Color{0x14, 0x14, 0x1b, 0xff};
const std::pair<Color, Color> PALETTE = {Color{0xb1, 0x93, 0xba, 0xff},
                                         Color{0x84, 0x66, 0x8e, 0xff}};

struct Track {
    std::string path;
    std::string title;
    std::string artist;
};

std::queue<Track> Playlist;

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

std::vector<std::string> split_string(std::string &str, int maxlen,
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

Track get_track() {
    std::string path = get_filepath();
    Track result = Track{path, "", ""};

    TagLib::FileRef f(path.data());

    if (!f.isNull() && f.tag()) {
        TagLib::Tag *tag = f.tag();
        result.artist = tag->artist().toCString(true);
        result.title = tag->title().toCString(true);
    }

    return result;
}

int main() {
    double volume = 0.1;
    bool is_paused = false;

    InitWindow(WIDTH, HEIGHT, "ray");
    InitAudioDevice();

    Track track = get_track();
    std::vector<std::string> title = split_string(track.title, 25, ' ');
    std::vector<std::string> author = split_string(track.artist, 30, ' ');
    Music music;
    music = LoadMusicStream(track.path.data());

    SetMusicVolume(music, volume);
    PlayMusicStream(music);
    while (!WindowShouldClose()) {
        UpdateMusicStream(music);

        if (IsKeyPressed(KEY_O)) {
            track = get_track();
            title = split_string(track.title, 25, ' ');
            author = split_string(track.artist, 30, ' ');

            UnloadMusicStream(music);
            music = LoadMusicStream(track.path.data());
            SetMusicVolume(music, 0.1);
            PlayMusicStream(music);
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
