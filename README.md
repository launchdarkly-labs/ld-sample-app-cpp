# LaunchDarkly Sample App for C++

## Requirements

* C++ 17+ compiler and dev tools
  - cmake 3.19+
  - boost 1.81+
  - openssl 1.1+
  - libpthread
  - drogon 1.9+

* LaunchDarkly Flags:
  - **Release: UI Enhancements**, key: `release-ui-enhancements`
  - **Release: Home Page Slider**, key: `release-home-page-slider`
  - **Coffee Promo 1**, key: `coffee-promo-1`
  - **Coffee Promo 2**, key: `coffee-promo-2`
  - **Banner Text**, key: `banner-text`

## Setup

NOTE: These specific instructions are for Ubuntu 24 LTS.

Install libraries and dev tools

```
apt update
apt install -y build-essential cmake openssl libc6-dev libpthread-stubs0-dev libboost-all-dev libjsoncpp-dev uuid-dev zlib1g-dev libssl-dev
```

Install Drogon

```
git clone https://github.com/drogonframework/drogon
cd drogon
git submodule update --init
mkdir build
cd build
cmake ..
make && sudo make install
cd ../..
```

Close this repo and the SDK repo and build the app

```
git clone https://github.com/launchdarkly-labs/ld-sample-app-cpp
cd ld-sample-app-cpp
git clone https://github.com/launchdarkly/cpp-sdks.git
cd cpp-sdks
mkdir build && cd build
cmake ..
cmake --build .
cmake --install .
cd ../..
mkdir build && cd build
cmake ..
cmake --build .
```

Add LaunchDarkly keys

* While still in the `build` directory, rename `.env.example` to `.env`
* In the `.env` file, replace the fake keys with your LaunchDarkly SDK key and client-side key

## Run

To run the site, from the `build` directory:

```
./ld-sample-app-cpp
```

In your browser, navigate to:

```
http://localhost:3000
```

Enjoy!
