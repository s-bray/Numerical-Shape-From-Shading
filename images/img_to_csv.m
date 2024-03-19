colorImg = imread('dog1-comp_baran.jpg');
grayImg = rgb2gray( colorImg );

fichier = fopen('dog3.csv','w');

fprintf(fichier,'%i\t %i\n',size(grayImg,1), size(grayImg,2));

for ii = 1:size(grayImg,1)
    fprintf(fichier,'%g\t',grayImg(ii,:));
    fprintf(fichier,'\n');
end

fclose(fichier);
