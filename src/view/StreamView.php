<?php

namespace axolotl\view;

use axolotl\util\_;

// Not extending PageView as no HTML-content has to be sent
class StreamView{
  public function __construct(
    $stream, string $filename
  ){
    $this->stream = $stream;
    header("Content-Disposition: attachment; filename=\"$filename\"");
    header("Content-Type: application/octet-stream");
  }

  public function render(): void{
    while(true){
      $cont = fread($this->stream, 1024);
      if($cont === false){
        break;
      }
      print($cont);
    }
  }
}
