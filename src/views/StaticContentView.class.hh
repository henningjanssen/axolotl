<?hh // strict

use axolotl\util\_;

// Not extending PageView as no HTML-content has to be sent
class StaticContentView{
  public function __construct(
    private string $content, private string $mimetype
  ){
    header("Content-Type: ".$this->mimetype);
  }

  public function render(){
    echo $content;
  }
}
