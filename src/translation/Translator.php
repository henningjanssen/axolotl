<?php

namespace axolotl\translation;

use axolotl\util\Log;
use \Exception;

class Translator {
  private static $instance;
  const DIR = __DIR__.'/../../locale/';

  private function __construct(string $locale) {
    $this->locale = $locale;
    try {
      $dirit = new \DirectoryIterator(self::DIR . $locale);
      $mtime = $this->fetchMtime($dirit);
      $lastMTime = apc_fetch('__axl_translation_mtime_' . $locale);
      if ($lastMTime !== false && $lastMTime >= $mtime) {
        return;
      }
      foreach ($dirit as $file) {
        $this->initFile($file);
      }

      apc_store('__axl_translation_mtime_' . $locale, $mtime);
    } catch (\UnexpectedValueException $e) {
      Log::warning("Translation", sprintf("Missing translation '%s'.", $locale));
    }
  }

  private function initFile(\SplFileInfo $fileInfo): void {
    $file = $fileInfo->openFile('r');
    $msgid = "";
    while (!$file->eof()) {
      $line = $file->fgets();
      if (substr($line, 0, strlen('msgid')) === 'msgid') {
        $msgid = substr($line, strlen('msgid') + 2, -2);
      } else if (substr($line, 0, strlen('msgstr')) === 'msgstr') {
        $msgstr = substr($line, strlen('msgstr') + 2, -2);
        apc_store(
          '__axl_translation_' . $this->getLocale() . $msgid,
          $msgstr
        );
      }
    }
  }

  private function fetchMtime(\DirectoryIterator $dirit): int {
    $mtime = 0;
    foreach ($dirit as $file) {
      $mtime = max($mtime, $file->getMTime());
    }
    $dirit->rewind();

    return $mtime;
  }

  public static function init(string $locale): Translator {
    return self::$instance = new Translator($locale);
  }

  public static function get(): Translator {
    if (!self::$instance) {
      throw new Exception("Translator not initialized!");
    }

    return self::$instance;
  }

  public static function getSupportedLocales(): array {
    $dirit = new \DirectoryIterator(self::DIR);
    $ret = [];
    foreach ($dirit as $dir) {
      if ($dir->isDir() && !$dir->isDot()) {
        $ret[] = $dir->getFilename();
      }
    }

    return $ret;
  }

  public function getLocale(): string {
    return $this->locale;
  }

  public function translate(string $msg): string {
    $translation = apc_fetch('__axl_translation_' . $this->getLocale() . $msg);
    if ($translation !== false) {
      return $translation;
    }

    return $msg;
  }
}
