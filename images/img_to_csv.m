colorImg = imread('pepper256.pgm');
% grayImg = rgb2gray( colorImg );
grayImg = colorImg;

fichier = fopen('pepper.csv','w');

fprintf(fichier,'%i\t %i\n',size(grayImg,1), size(grayImg,2));

for ii = 1:size(grayImg,1)
    fprintf(fichier,'%g\t',grayImg(ii,:));
    fprintf(fichier,'\n');
end

fclose(fichier);
