<?hh // strict

namespace axolotl\module;

use \axolotl\entities\Module;
use \axolotl\entities\RoutingInfo;

interface ModuleControl{
  public function install(): bool;
  public function uninstall(): bool;
  public function update(): bool;
  public function backup(): void;
  public function getRoutings(Module $module): array<RoutingInfo>;
}
