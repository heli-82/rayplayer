cmake -B build
cd build
cmake .. && make
cd ..
cp build/ray $HOME/.local/bin/
cp ray.desktop $HOME/.local/share/applications
