# ssa-cpp
C++ rewrite of yaabex/ssa

#How to use
* To do the alignment, build with cmake and use the executable created with the first argument being the script and the second being the subtitle file (NOTE: remember to remove the page break chars from the script). It will produce the results in a txt file
* To extract the audio from the movie, use the audio_extractor script, which takes as its first argument the result file from an alignemnt and as the second argument the movie file
