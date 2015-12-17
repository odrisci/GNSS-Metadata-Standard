clear all;
fpt=fopen( 'RoofTop_FE0_Band0.stream', 'rb' );
sampt=fread( fpt, 1000, 'bit2' );
sampt=2*sampt+1;
fclose( fpt );

fp=fopen( 'L1.dat', 'rb' );
samp = fread( fp, 1000, 'int8' );
fclose( fp );

plot( sampt, samp );