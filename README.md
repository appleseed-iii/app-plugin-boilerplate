# app-plugin-olympus

## forked from app-plugin-boilerplate

## Steps used to create your local project

1. create a new directory to hold this project. You will clone app-ethereum, ledger plugin-tools & app-plugin-boilerplate into this new directory

2. clone app-ethereum

    ```bash
    git clone --recurse-submodules git@github-appleseed:LedgerHQ/app-ethereum.git
    ```

3. clone ledger plugin-tools

    ```bash
    git clone git@github-appleseed:LedgerHQ/plugin-tools.git
    ```

4. make app-ethereum

    ```bash
    cd plugin-tools
    ./start.sh
    ```

    in docker

    ```bash
    # your docker directory
    # root@997ccff31349:/plugin_dev$ ls
    #=> app-ethereum  plugin-tools

    cd app-ethereum
    make

    # when done
    exit
    ```

5. now you'll have `app-ethereum/bin` files
6. clone the boiler-plate repo

    ```bash
    cd ..
    git clone --recurse-submodules git@github-appleseed:appleseed-iii/app-plugin-boilerplate.git
    ```

7. after updating tests

    To build the plugin, you will need to go back to your docker setup. Fire up a new terminal window, go to your plugin_dev folder, and run ./start.sh.

    In your container, go to the plugin repo, and in the tests folder.

    ```bash
    cd app-plugin-boilerplate/tests
    ```

## Formatting

The C source code is expected to be formatted with `clang-format` 11.0.0 or higher.
