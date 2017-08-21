<?hh // strict

namespace axl\translator\control;

use axolotl\control\LoggedInPageControl;

class ListTranslationsControl extends LoggedInPageControl {
  <<__Override>>
  public function execute(): void {
    $dirit = new \DirectoryIterator(__DIR__ . '/../../../../locale');
    $locales = [];
    foreach ($dirit as $file) {
      if ($file->isDot()) continue;
      $locales[] = $file->getFilename();
    }
    (new \ListTranslationsView($locales))->render();
  }
}
