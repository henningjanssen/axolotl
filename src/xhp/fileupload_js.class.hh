<?hh // strict

use axolotl\util\_;

/**
 * This class exists because a javascript-call via XHPJS needs to be placed
 * inside a xhp-class that is surrounded by a :x:js-scope tag.
 * The fileupload tag should not have to be surrounded with these tags
 * as that would only provide discomfort and result in unnecessary much and
 * unreadable code. This class' only purpose is to be used as a child
 * of fileupload.
 */
class :fileupload_js extends :x:element{
  //we use js
  use XHPJSCall;

  //attributes
  attribute string name @required;
  attribute string accept = "";
  attribute boolean drop = false;
  attribute boolean multi = false;

  children empty;

  public function render(): \XHPRoot{
    $baseuri = strval(_::SETTINGS("axolotl_base_uri", ""));
    $this->jscall(
      'FileUpload',
      'register',
      $this->:name,
      Map{
        'target' => "$baseuri/api/upload/{$this->:name}",
        'chunkSize' => intval(_::SETTINGS('upload_chunksize', 1*1024*1024)),
        'forceChunkSize' => true,
        'simultaneousUploads' => boolval(_::SETTINGS('upload_simul', 3)),
        'fileType' => explode(".", $this->:accept),
        'query' => Map{'upload_token' => $this->:name}
      },
      $this->:drop
    );
    return <x:frag/>;
  }
}
