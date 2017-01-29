<?hh // strict

namespace axolotl\util;

use \axolotl\exceptions\NonExistentFileException;

class UploadedZipFile extends UploadedFile{
  public function listContents(): array<string>{
    if(!$this->exists()){
      throw new NonExistentFileException();
    }
    $contents = array();
    $zip = new \ZipArchive();
    $zip->open($this->path);
    for($i = 0; $i < $zip->numFiles; $i++){
      $contents[] = $zip->getNameIndex($i);
    }
    $zip->close();
    return $contents;
  }

  public function extractTo(string $path): void{
    $zip = new \ZipArchive();
    $zip->open($this->path);
    $zip->extractTo($path);
    $zip->close();
  }
}
