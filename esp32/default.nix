let
  nixpkgs-esp-dev = builtins.fetchGit {
    url = "https://github.com/mirrexagon/nixpkgs-esp-dev.git";
  };

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
