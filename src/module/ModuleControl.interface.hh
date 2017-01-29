<?hh // strict

namespace axolotl\module;

interface ModuleControl{
  public function install(): bool;
  public function uninstall(): bool;
  public function update(): bool;
  public function backup(): void;
}
