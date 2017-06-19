
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
	//очищение для локальной обработки
});










function isCopy (file)
{
	var hash = hash_of_file(file);
	if (typeof LIST_HASH[hash] == "undefined")
	{
		LIST_HASH[hash] = 1;
		return false;
	}
	else
		return true;
}











var LIST_HASH = {};
function processing_of_files (file)
{

	$('.stats').append("<br>processing: " + file + " " + isCopy(file));
}











var fs = require('fs');
var path = require('path');
var getFiles = function (dir, files_){
	files_ = files_ || [];
	var files = fs.readdirSync(dir);
	for (var i in files){
		var name = dir + '\\' + files[i];
		if (fs.statSync(name).isDirectory()){
			getFiles(name, files_);
		} else {
			files_.push(name);
		}
	}
	return files_;
};












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












const crypto = require('crypto');
var fs = require('fs');
function hash_of_file(filename)
{
	const hash = crypto.createHash('md5');

	// const input = fs.createReadStream(filename);
	// input.on('readable', () => {
	// 	var data = "alica"; //input.read();
	// 	if (data)
	// 		hash.update(data);
	// 	else {
	// 		text_hash += hash.digest('hex');
	// 	}
	// });
	var text = fs.readFileSync(filename, 'utf8');
	hash.update(text);

	return hash.digest('hex');
}