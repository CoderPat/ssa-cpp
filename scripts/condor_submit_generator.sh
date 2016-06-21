#creates a condor submit file for dataset extraction based on a base folder with movie folders

base_folder="../test_folder/"
movie_extraction_script="bash movie_extractor.sh"

condor_base="
executable              = $movie_extraction_script
universe                = vanilla
notification            = error
log                     = condor_output/gmm_estimation.condor.log
requirements            = (ARCH == \"X86_64\") && (Machine == \"x02.l2f.inesc-id.pt\" || Machine == \"x03.l2f.inesc-id.pt\" || Machine == \"x04.l2f.inesc-id.pt\" || Machine == \"x05.l2f.inesc-id.pt\" || Machine == \"x06.l2f.inesc-id.pt\" || Machine == \"x07.l2f.inesc-id.pt\" || Machine == \"x08.l2f.inesc-id.pt\" || Machine == \"x09.l2f.inesc-id.pt\" || Machine == \"x10.l2f.inesc-id.pt\" || Machine == \"x11.l2f.inesc-id.pt\" || Machine == \"x12.l2f.inesc-id.pt\" || Machine == \"x13.l2f.inesc-id.pt\" || Machine == \"x14.l2f.inesc-id.pt\")
"

echo "${condor_base}" > dataset_extraction.submit

for movie_folder in ${base_folder}*/; do
	echo "arguments				= \"$movie_folder\"" >> dataset_extraction.submit
	echo "queue" >> dataset_extraction.submit
done
