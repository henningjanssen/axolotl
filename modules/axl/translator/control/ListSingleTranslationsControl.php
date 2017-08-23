<?hh // strict

namespace axl\translator\control;

use axolotl\control\LoggedInPageControl;
use axolotl\util\PathUtil;

class ListSingleTranslationsControl extends LoggedInPageControl {
  <<__Override>>
  public function execute(): void {
    $dirit = new \DirectoryIterator(PathUtil::ROOT . 'locale/' . $this->vars['lang']);
    $strings = Map {};
    foreach ($dirit as $file) {
      if ($file->isDot()) continue;
      $strings->setAll($this->getTranslations($file->openFile('r')));
    }
    (new \ListSingleTranslationsView($strings))->render();
  }

  private function getTranslations(\SplFileObject $file): Map<string, string> {
    $id = "";
    $ret = Map {};
    while (!$file->eof()) {
      $line = $file->fgets();
      if (substr($line, 0, strlen('msgid')) === 'msgid') {
        $id = substr($line, strlen('msgid') + 2, -2);
      } else if (substr($line, 0, strlen('msgstr')) === 'msgstr') {
        $ret[$id] = substr($line, strlen('msgstr') + 2, -2);
      }
    }

    return $ret;
  }
}
