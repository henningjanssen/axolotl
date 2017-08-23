<?hh // strict

namespace axl\translator\control;

use axolotl\util\Doctrine;
use axolotl\control\LoggedInPageControl;
use axolotl\util\PathUtil;
use axolotl\entities\Module;

class ListTranslationsControl extends LoggedInPageControl {
  <<__Override>>
  public function execute(): void {
    $dirit = new \DirectoryIterator(PathUtil::ROOT . 'locale');
    $locales = [];
    foreach ($dirit as $file) {
      if ($file->isDot()) continue;
      $locales[] = $file->getFilename();
    }
    (new \ListTranslationsView($locales, $this->getModule()))->render();
  }

  private function getModule(): Module {
    // TODO Generic module fetching approach
    return Module::getByName('AXL', 'Translator');
  }
}
