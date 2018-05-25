<?php

namespace axolotl\view;

use axolotl\util\_;

// Not extending PageView as no HTML-content has to be sent
class StreamView{
  public function __construct(
    $stream, string $filename, $forceDownload = true,
    $contentType = "application/octet-stream", int $initialOffset = 0,
    $flush = true
  ){
    $this->stream = $stream;
    $this->initialOffset = $initialOffset;
    $this->flush = $flush;
    $contentDisp = $forceDownload ?'attachment' :'inline';
    header("Content-Disposition: $contentDisp; filename=\"$filename\"");
    header("Content-Type: $contentType");
  }

  public function render(): void{
    $offset = $this->initialOffset;
    while(true){
      $cont = stream_get_contents($this->stream, 1024, $offset);
      $offset = -1;
      if($cont === false){
        break;
      }
      echo $cont;
      if($this->flush){
        ob_flush();
      }
    }
  }
}
