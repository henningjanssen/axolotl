<?hh // strict

use axolotl\util\_;
use axolotl\util\Session;

abstract class PageView{
  protected :xhp $head;
  protected :xhp $precontent; //navbar, etc
  protected :xhp $content;
  protected :xhp $postcontent; //footer, etc.
  protected :xhp $baseuri;

  public function __construct(string $title = ""){
    $vendor = strval(_::SETTINGS("vendor", "axolotl"));
    if(strlen($title) > 0 && strlen($vendor) > 0){
      $title .= " | ";
    }
    if(strlen($vendor) > 0){
      $title .= $vendor;
    }
    $this->baseuri = _::SETTINGS("axolotl_base_uri", "");
    $this->head =
      <head>
        <meta charset="utf-8"/>
        <meta name="robots" content="noindex,nofollow"/>
        <title>{$title}</title>
        <script src="//code.jquery.com/jquery-1.11.0.min.js"></script>
        <link
          rel="stylesheet"
          href="//maxcdn.bootstrapcdn.com/bootstrap/3.2.0/css/bootstrap.min.css"
        />
        <script src="//code.jquery.com/jquery-1.11.0.min.js"/>
        <script
          src="//maxcdn.bootstrapcdn.com/bootstrap/3.2.0/js/bootstrap.min.js"
        />
      </head>;
    $this->precontent = $this->getPrecontent();
    $this->content = <x:frag/>;
    $this->postcontent = <x:frag/>;
  }

  final private function getPrecontent(): :xhp{
    $navbar =
      <bootstrap:navbar>
        <bootstrap:navbar:brand href="#">
          AXL
        </bootstrap:navbar:brand>
      </bootstrap:navbar>;

    if(Session::loggedIn()){
      $navbar->appendChild(
        <x:frag>
          <bootstrap:navigation:link href={$this->baseuri.'/home'}>
            Home
          </bootstrap:navigation:link>
          <bootstrap:navigation:link href={$this->baseuri.'/logout'}>
            Logout
          </bootstrap:navigation:link>
        </x:frag>
      );
    }
    else{
      $navbar->appendChild(
        <bootstrap:navigation:link href="{$this->baseuri.'login'}">
          Login
        </bootstrap:navigation:link>
      );
    }
    return $navbar;
  }

  final public function setHeader(string $header): void{
    header($header);
  }

  final public function setHTTPStatusCode(int $code): void{
    http_response_code($code);
  }

  final public function render(): void{
    print(
      <x:doctype>
        <html>
          {$this->head}
          <body>
            {$this->precontent}
            {$this->content}
            {$this->postcontent}
          </body>
        </html>
      </x:doctype>
    );
  }
}
