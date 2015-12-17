

clear all;

MAC = 0;
WIN = 1;

SYS = WIN;

if SYS == WIN
    testDir    = pwd;
    % I store and run this matlab script from the same directory that the
    % repo is kept, so that the below path works.
    installDir = '..';
    binName    = 'TestApp_vs';
elseif SYS == MAC
    %testDir    = pwd;
    %installDir = '/Volumes/Data/GitHub/GNSS-Metadata-Standard/Converter/install/';
    %binName    = './TestApp';
else
    printf('System??\n');
end



cd(installDir);
system('rm *.dat');
system(binName);
cd(testDir);

nSamples = 1024*1024;

origFileDataType = 'int8';
newFileDataType  = 'int8';

fileL1Original = fopen('ref_1.dat', 'rb');
fileL2Original = fopen('ref_2.dat', 'rb');
fileL5Original = fopen('ref_3.dat', 'rb');

dataL1Original = fread( fileL1Original, nSamples, origFileDataType );
dataL2Original = fread( fileL2Original, nSamples, origFileDataType );
dataL5Original = fread( fileL5Original, nSamples, origFileDataType );

fileL1New = fopen(sprintf('L1.dat'));
fileL2New = fopen(sprintf('L2.dat'));
fileL5New = fopen(sprintf('L5.dat'));


if( fileL1New > 0 )
    dataL1New = fread( fileL1New, nSamples, newFileDataType );
    if( dataL1Original ==  dataL1New )
        fprintf('File L1 OK\n');
    else
        fprintf('File L1 Broken!\n');
    end
else
    fprintf('File L1 Missing!\n')
end

if( fileL2New > 0 )
    dataL2New = fread( fileL2New, nSamples, newFileDataType );
    if( dataL2Original ==  dataL2New )
        fprintf('File L2 OK\n');
    else
        fprintf('File L2 Broken!\n');
    end
else
    fprintf('File L2 Missing!\n')
end

    
if( fileL5New > 0 )
    dataL5New = fread( fileL5New, nSamples, newFileDataType );
    if( dataL5Original ==  dataL5New )
        fprintf('File L5 OK\n');
    else
        fprintf('File L5 Broken!\n');
    end
else
    fprintf('File L5 Missing!\n')
end


fclose all;
