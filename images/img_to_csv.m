colorImg = imread('dog1.png');
grayImg = rgb2gray( colorImg );

fichier = fopen('dog.csv','w');

fprintf(fichier,'%i\t %i\n',size(grayImg,1), size(grayImg,2));

for ii = 1:size(grayImg,1)
    fprintf(fichier,'%g\t',grayImg(ii,:));
    fprintf(fichier,'\n');
end

fclose(fichier);