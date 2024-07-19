{
  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixpkgs-unstable";
    systems.url = "github:nix-systems/x86_64-linux";

    flake-utils = {
      url = "github:numtide/flake-utils";
      inputs.systems.follows = "systems";
    };
  };
  outputs = inputs @ {flake-utils, ...}:
    flake-utils.lib.eachDefaultSystem (system: let
      pkgs = inputs.nixpkgs.legacyPackages.${system};
      configGen = pkgs.callPackage ./nix/configGen.nix {};
    in {
      devShells.default = pkgs.mkShell {
        name = "shell";
        inputsFrom = [configGen];
      };
      packages = {
        inherit configGen;
      };
    });
}
