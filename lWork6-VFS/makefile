src_dir := .
SRC_FILES := $(wildcard $(src_dir)/*.c)
FILES := $(patsubst $(src_dir)/%.c, $(src_dir)/%, $(SRC_FILES))

all: $(FILES) message

message:
	$(info                                        )
	$(info ***************************************)
	$(info ********** FUNCTION SYNOPSIS **********)
	$(info ***************************************)
	$(info ./write_file [file_name] [TEXT])
	$(info ./read_file [FILE_NAME]       )
	$(info ./read_file_from_end [FILE_NAME]		 )

$(src_dir)/%: $(src_dir)/%.c
	gcc -o $@ $^

clean:
	rm -rf $(FILES)