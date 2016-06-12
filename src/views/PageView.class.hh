<?hh // strict


abstract class PageView{
  protected :xhp $head;
  protected :xhp $precontent; //navbar, etc
  protected :xhp $content;
  protected :xhp $postcontent; //footer, etc.

  public function __construct(string $title = "axolotl"){
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
    $this->precontent = <x:frag/>;
    $this->content = <x:frag/>;
    $this->postcontent = <x:frag/>;
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
