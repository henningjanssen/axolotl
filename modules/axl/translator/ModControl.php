<?hh // strict

namespace axl\translator;

use \axolotl\entities\RoutingInfo;
use \axolotl\entities\Module;
use \axl\translator\control\ListTranslationsControl;

class ModControl implements \axolotl\module\ModuleControl {
  public function install(): bool{
		// Everything that belongs to installation has to be implemented here.
    return true;
	}

  public function uninstall(): bool{
		// Every step that is required for uninstalling this module needs to
		// be implemented here
    return true;
	}

  public function update(): bool{
		// If the module has been updated, this function gets executed
    return true;
	}

  public function backup(): void{
		// If the user wants to backup his stuff, this function is called
	}

  public function getRoutings(Module $module): array<RoutingInfo>{
    return array(
      RoutingInfo::newInstance($module, '/list', ListTranslationsControl::class)
    );
  }

}
