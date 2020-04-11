# How to install

1. Install boost
2. Build boost for filesystem
3. In order to run add shared libraries to `LD_LIBRARY_PATH`:
    ```shell
    export LD_LIBRARY_PATH=/lib:/usr/lib:/usr/local/lib:/usr/local/boost_1_72_0/stage/lib
    ```