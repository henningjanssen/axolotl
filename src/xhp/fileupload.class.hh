<?hh // strict

class :fileupload extends :x:element{
  //attributes
  attribute
    string id @required,
    string name @required,
    string accept = "",
    boolean drop = false,
    boolean multi = false;

  //no children allowed!
  children empty;

  protected function render(): \XHPRoot{
    $elem = <div id={$this->:id}/>;
    $elem->appendChild(
      <input type="hidden" id={$this->:name."_upload_input"} name={$this->:name}/>
    );
    $elem->appendChild(
      <button id={$this->:name."_upload_btn"}></button>
    );
    $elem->appendChild(
      <x:js-scope>
        <fileupload_js name={$this->:name} accept={$this->:accept}
          drop={$this->:drop} multi={$this->:multi}/>
      </x:js-scope>
    );
    return $elem;
  }
}
