var FileUpload = {
  register: function(id, args, drop = false){
    var r = new Resumable();
    r.assignBrowse(document.getElementById(id+"_upload_btn"));
    if(dragdrop){
      r.assignDrop(document.getElementById(id+"_upload_drop"));
    }
    r.on('fileSuccess', function(file, message){
      //
    });
    r.on('fileError', function(file, message){
      //
    });
  };
  return{
    register: register
  };
};

if (typeof module != 'undefined'){
  module.exports = FileUpload;
}
else{
  window.fileupload = fileupload;
}
