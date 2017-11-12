<?hh // strict

use \axolotl\util\_;

class :axolotl:xhp:fileupload extends :x:element{
  //attributes
  attribute
    string id @required,
    string name @required,
    string accept = "",
    bool drop = false,
    bool multi = false,
    enum {
        'success',
        'info',
        'warning',
        'danger',
    } use = 'info',
    enum {
        'off',     // Solid
        'on',      // Striped
        'active'   // Striped and moving
    } stripes = 'off';

  //no children allowed!
  children empty;

  protected function render(): \XHPRoot{
    $elem = <div id={$this->:id}/>;
    $elem->appendChild(
      <input type="hidden" id={$this->:name."_upload_filename"} name={$this->:name}/>
    );
    $elem->appendChild(
      <bootstrap:button-group>
        <bootstrap:button
          id={$this->:name."_upload_btn"} use="primary">
          {t('Choose file')}
          <span class="glyphicon glyphicon-open" aria-hidden="true"></span>
        </bootstrap:button>
        <bootstrap:button
          id={$this->:name."_upload_startbtn"} use="success">
          <span class="glyphicon glyphicon-play" aria-hidden="true"></span>
        </bootstrap:button>
      </bootstrap:button-group>
    );
    $elem->appendChild(
      <bootstrap:progress-group>
        <bootstrap:progress-bar use={$this->:use} stripes={$this->:stripes}
          id={$this->:name."_upload_progressbar"} value={0}>
        </bootstrap:progress-bar>
      </bootstrap:progress-group>
    );
    $baseuri = strval(_::SETTINGS('system.base_uri', ''));

    /* This variable is needed because XHP cannot handle curly braces inside a
     * script tag at the moment. hhvm/xhp-js causes linter-errors in
     * facebook/xhp-lib somehow. So this is a workaround until I find a
     * better one or the bugs get fixed.
     */
    $script = "
      FileUpload.register(
        \"{$this->:name}\",
        {
          target: \"$baseuri/api/upload/{$this->:name}\",
          chunkSize: ".strval(_::SETTINGS('upload.chunksize', 1*1024*1024)).",
          forceChunkSize: true,
          simultaneousUploads: ".strval(_::SETTINGS('upload.simul', 3)).",
          fileType: [\"".str_replace(";", ", ", $this->:accept)."\"],
          query: {upload_token: \"{$this->:name}\"}
        },
        ".($this->:drop?"true":"false")."
      );
    ";
    $elem->appendChild(
      <script type="text/javascript">{strval($script)}</script>
    );
    return $elem;
  }
}
