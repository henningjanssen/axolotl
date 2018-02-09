<?php

function getIds(string $file): array {
  $fo = new \SplFileObject($file, 'r');
  $ret = [];
  while (!$fo->eof()) {
    $line = $fo->fgets();
    if (substr($line, 0, strlen('msgid')) == 'msgid') {
      $ret[] = substr($line, strlen('msgid') + 2, -2);
    }
  }

  return $ret;
}

function translate(string $msg, string $language): string {
  $url = 'https://translate.googleapis.com/translate_a/single?client=gtx&sl=';
  $url .= 'en&tl=' . $language . '&dt=t&q='.urlencode($msg);
  $ch = curl_init();

  curl_setopt($ch, CURLOPT_URL, $url);
  curl_setopt($ch, CURLOPT_RETURNTRANSFER, 1);

  $result = json_decode(curl_exec($ch), true);
  return $result[0][0][0];
}

if ($argc != 3) {
  echo "Unexpected Arguments. Must be: file language", PHP_EOL;
  echo "File is the .po file generated by:", PHP_EOL;
  echo "\t xgettext -kt -k_t --language=PHP src/**/*.php -o -", PHP_EOL;
  echo "Langauge is a abbreviation of the target language, i.e.: de", PHP_EOL;
  exit(1);
}
$file = $argv[1];
$language = $argv[2];
$ids = getIds($file);

foreach ($ids as $id) {
  $translation = translate($id, $language);
  printf('msgid "%s"', $id);
  echo PHP_EOL;
  printf('msgstr "%s"', $translation);
  echo PHP_EOL, PHP_EOL;
}