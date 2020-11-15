# cutmidel

![Status](https://github.com/prantlf/cutmidel/workflows/release/badge.svg)

Trims a text to a maximum length by putting an allipsis to the middle of the shortened result.

    $ cutmidel "~/Sources/private/cutmidel" 5 10
    ~/Sou...e/cutmidel

Can be used to cut too long parts of a custom shell prompt. For example, setting the following environment variable:

    export PROMPT_COMMAND='PS1="\u@\h:$(cutmidel \"$PWD\" 0 12 ..) "'

will result in a prompt like this in the directory `~/Sources/private/cutmidel` with BASH:

    prantlf@noto:..ate/cutmidel

See also [shortpwd] if you want to shorten the current working directory.

## Installation

Make sure that you have Git client, C buildchain, GNU Make and CMake installed. Clone this repository, build, test and install the executable and manpage to the directory you choose:

    git clone https://github.com/prantlf/cutmidel.git
    cd cutmidel
    mkdir build
    cd build
    cmake ..
    make test install

You can change the default build type and installation prefix too:

    cmake -DCMAKE_INSTALL_PREFIX=/usr/local  -DCMAKE_BUILD_TYPE=Release ..

## Usage

    cutmidel [options] <text> <leading> <trailing> [ellipsis]

Specify the text and the maximum count of leading and trailing characters. The overall maximum length will be their sum plus the length of an ellipsis (3 dots by default). Zero for either leading or trailing count means no leading or trailing parts.

## Options

    -V|--version  prints the version of the executable and exits
    -h|--help     prints the usage information and exits

[shortpwd]: https://github.com/prantlf/shortpwd
