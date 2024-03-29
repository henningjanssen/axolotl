var FileUpload = {
  register: function(id, args, dragdrop = false){
    var r = new Resumable(args);

    if(!r.support){
      alert(
        "Your system does not allow uploads with resumable.js."
        +"You need active Javascript and HTML5-support."
      );
      return;
    }
    r.assignBrowse(document.getElementById(id+"_upload_btn"));
    if(dragdrop){
      r.assignDrop(document.getElementById(id+"_upload_drop"));
    }
    $("#"+id+"_upload_startbtn").click(function(){
      if(r.files.length > 0){
        if(r.isUploading()){
          return r.pause();
        }
        return r.upload();
      }
    });
    r.on('fileSuccess', function(file, message){
      $("#"+id+"_upload_filename").val(file.fileName);
    });
    r.on('fileError', function(file, message){
      alert("There was an error uploading the file '"
        +file.fileName+"': "+message);
    });
    r.on('progress', function(){
      $("#"+id+"_upload_startbtn").find('.material-icons')
        .text('pause')
      $("#"+id+"_upload_progressbar")
        .attr('style', 'width:'+(r.progress()*100)+'%')
        .attr('aria-valuenow', r.progress() * 100);
    });
    r.on('pause', function(){
      $("#"+id+"_upload_startbtn").find('.material-icons')
        .text('play_arrow')
    });
  }
};

if (typeof module != 'undefined'){
  module.exports = FileUpload;
}
else{
  window.FileUpload = FileUpload;
}
