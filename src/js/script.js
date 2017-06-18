// Mixing jQuery and Node.js code in the same file? Yes please!

$(function()
{

});



function data_of_form ()
{
	var arr_data = {};
	arr_data["list_input_folder"] = $("#list_input_folder").val();
	arr_data["output_folder"] = $("#output_folder").val();
	arr_data["type_mover"] = ($("#copy").prop("checked")) ? "copy" : "move";
	arr_data["remove_copies"] = $("#ubrat_copy").prop("checked");
	arr_data["type_remove_copies"] = ($("#global").prop("checked")) ? "global" : "local";

	return arr_data;
}

 

 


var fs = require('fs');
var path = require('path');
var getFiles = function (dir, files_){
	files_ = files_ || [];
	var files = fs.readdirSync(dir);
	for (var i in files){
		var name = dir + '/' + files[i];
		if (fs.statSync(name).isDirectory()){
			getFiles(name, files_);
		} else {
			files_.push(name);
		}
	}
	return files_;
};
$("#group_proceccing_1").click(function()
{
	var arr_data = data_of_form();
	var folders = arr_data["list_input_folder"].split('\n');

	jQuery.each(folders, function(i, str_path)
	{
		var list_files = getFiles(str_path);
		jQuery.each(list_files, function(i, file)
		{
			processing_of_files(file);
		});
	});
});








function processing_of_files (file)
{
	$('.stats').append("<br>processing: " + file);
}