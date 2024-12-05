# A standalone shell definition that overrides the versions of ESP-IDF
# and the ESP32 toolchain.
#
# Repo: https://github.com/mirrexagon/nixpkgs-esp-dev

let
  nixpkgs-esp-dev = builtins.fetchGit {
    url = "https://github.com/mirrexagon/nixpkgs-esp-dev.git#esp32-idf";
  };

  rev = "31ee58005f43e93a6264e3667c9bf5c31b368733";

  pkgs = import <nixpkgs> {
    overlays = [ (import "${nixpkgs-esp-dev}/overlay.nix") ];
  };
in pkgs.mkShell {
  name = "esp-project";

  buildInputs = with pkgs; [
    (esp-idf-esp32.override {
      rev = "v5.3.1";
      sha256 = "sha256-hcE4Tr5PTRQjfiRYgvLB1+8sR7KQQ1TnQJqViodGdBw=";
    })

    cmake
    clang-tools
    gnumake
  ];
}
