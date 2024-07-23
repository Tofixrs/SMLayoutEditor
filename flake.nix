{
  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixpkgs-unstable";
    flake-parts = {
      url = "github:hercules-ci/flake-parts";
      inputs.nixpkgs-lib.follows = "nixpkgs";
    };
    mygui = {
      url = "github:MyGui/mygui/dae9ac4be5a09e672bec509b1a8552b107c40214";
      flake = false;
    };
  };
  outputs = inputs @ {flake-parts, ...}:
    flake-parts.lib.mkFlake {inherit inputs;} (_: {
      systems = ["x86_64-linux"];
      imports = [
        {config._module.args._inputs = inputs // {inherit (inputs) self;};}
        ./parts
      ];
    });
  nixConfig = {
    substituters = ["https://sm-gui-editor.cachix.org"];
    trusted-public-keys = ["sm-gui-editor.cachix.org-1:sOHlz7KeslsRSBiGfE5G4Hbm7URIdtaI1zZSeL92m3s="];
  };
}
