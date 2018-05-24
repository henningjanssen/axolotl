<?php

namespace axolotl\util;

use \axolotl\entities\Module;
use \axolotl\exceptions\NonExistentFileException;
use \axolotl\exceptions\InvalidArgumentException;

class UploadedFile{
  protected $filename;
  protected $path;
  public function __construct(string $inputname){
    $this->inputname = $inputname;
    $this->filename = strval(_::POST($inputname));
    $this->path = realpath(__DIR__."/../../uploads/".$this->filename);
  }

  public function exists(): bool{
    return file_exists($this->path);
  }

  public function getFilename(): string{
    return $this->filename;
  }

  public function getPath(): string{
    return $this->path;
  }

  public function getExtension(): string{
    $dotpos = strrpos($this->filename, ".");
    $ext = "";
    if($dotpos !== false){
      $ext = substr($this->filename, $dotpos+1);
    }
    return $ext;
  }

  public function getMimeType(): string{
    if(!$this->exists()){
      throw new NonExistentFileException(
        "Uploaded file `{$this->filename}` does not exist"
      );
    }
    return strval(mime_content_type($this->path));
  }

  public function moveTo(
    string $path, ?Module $module = null, bool $fnameInc = true
  ): void{
    $newpath = realpath(__DIR__."/../..");
    if($module !== null){
      $newpath .= "/modules/".$module->getPath();
    }
    $newpath .= "/".$path;
    if(!$fnameInc){
      $newpath .= "/".$this->filename;
    }
    if(!rename($this->path, $newpath)){
      throw new InvalidArgumentException(
        "Moving uploaded file `{$this->path}` failed"
      );
    }
  }

  public function delete(): void{
    if(!$this->exists()){
      return;
    }
    unlink($this->path);
  }
}
