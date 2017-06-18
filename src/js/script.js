// Mixing jQuery and Node.js code in the same file? Yes please!

$(function(){
	var os = require('os');
		var prettyBytes = require('pretty-bytes');
/*
	$('.stats').append('Number of cpu cores: <span>' + os.cpus().length + 'asdf</span>');
	$('.stats').append('Free memory: <span>' + prettyBytes(os.freemem()) + 'adf</span>');
*/

	var gui = require('nw.gui');
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

 

 
function processing_of_files (file)
{
    return function(err, stats) {
            $('.stats').append("<br>processing: " + file + "\n\n");
        }
}
function read_folder_recursion (fs, str_path)
{
	fs.readdir(str_path, function(err, items) {
		for (var i = 0; i < items.length; i++) {
			var filing_obj = str_path + '/' + items[i];
			
			read_folder_recursion(fs, filing_obj);
			fs.stat(filing_obj, processing_of_files(filing_obj));
		}
	});
}
$("#group_proceccing_1").click(function(){
	var arr_data = data_of_form();
	var folders = arr_data["list_input_folder"].split('\n');
	jQuery.each(folders, function(i, str_path)
	{
		var fs = require('fs');
		read_folder_recursion(fs, str_path);
	});
});