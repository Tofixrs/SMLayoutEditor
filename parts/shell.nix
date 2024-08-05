_: {
  perSystem = {
    pkgs,
    self',
    ...
  }: {
    devShells = {
      default = pkgs.mkShell {
        name = "shell";
        inputsFrom = [self'.packages.configGen];
      };
      mygui = pkgs.mkShell {
        name = "mygui-shell";
        inputsFrom = [self'.packages.mygui];
      };
      flatpak = pkgs.mkShell {
        name = "flatpak";
        packages = with pkgs; [
          appstream
        ];
      };
    };
  };
}
