#include <algorithm>
#include <cstdio>
#include <iostream>
#include <ostream>
#include <raylib.h>
#include <stdlib.h>
#include <string>
#include <taglib/fileref.h>
#include <taglib/tag.h>
#include <vector>

const int WIDTH = 300;
const int HEIGHT = 100;

const std::string TRACK = "../assets/Undertale - ＊ Despite Everything, It's "
                          "Still You [Instrumental Version].mp3";

struct MetaData {
    std::string title;
    std::string artist;
};

std::string get_path() {
    char path[1024];
    FILE *f = popen("zenity --file-selection --file-filter=*.mp3", "r");
    std::fgets(path, 1024, f);
    std::string strpath = path;
    std::cout << strpath << std::endl;
    return strpath.substr(0, strpath.length() - 1);
}

MetaData get_meta(std::string path) {
    MetaData result = MetaData{"", ""};

    TagLib::FileRef f(path.data());

    if (!f.isNull() && f.tag()) {
        TagLib::Tag *tag = f.tag();
        result.artist = tag->artist().toCString(true);
        result.title = tag->title().toCString(true);
    }

    return result;
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
               predicted > 0) {
            predicted--;
        }
        result.push_back(str.substr(current, predicted - current + 1));
        current = predicted + 1;
    }
    return result;
}

struct Track {
    std::string path;
    std::vector<std::string> title;
    std::vector<std::string> author;
};

Track preparation() {
    std::string path = get_path();
    path = (path != "") ? path : TRACK;
    MetaData data = get_meta(path);
    std::vector<std::string> title = split_string(data.title, 25, ' ');
    std::vector<std::string> author = split_string(data.artist, 30, ' ');
    return Track{path, title, author};
}

int main() {
    Track track = preparation();

    InitWindow(WIDTH, HEIGHT, "ray");

    InitAudioDevice();

    Music music;

    music = LoadMusicStream(track.path.data());
    SetMusicVolume(music, 0.1);
    PlayMusicStream(music);

    while (!WindowShouldClose()) {
        UpdateMusicStream(music);

        if (IsKeyPressed(KEY_O)) {
            track = preparation();
            UnloadMusicStream(music);
            music = LoadMusicStream(track.path.data());
            SetMusicVolume(music, 0.1);
            PlayMusicStream(music);
        }

        BeginDrawing();
        ClearBackground(BLACK);

        int title_shift = 0;
        for (std::string line : track.title) {
            DrawText(line.data(), 10, 10 + 20 * title_shift, 20, GREEN);
            title_shift++;
        }

        int author_shift = 0;
        for (std::string line : track.author) {
            DrawText(line.data(), 10, 10 + 20 * title_shift + 10 * author_shift,
                     10, DARKGREEN);
            author_shift++;
        }
        EndDrawing();
    }

    UnloadMusicStream(music);
    CloseAudioDevice();
    CloseWindow();

    return 0;
}
