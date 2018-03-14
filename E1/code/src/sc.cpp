
#include "sc.h"
#include <stdlib.h>
#include <algorithm>

using namespace cv;
using namespace std;


bool seam_carving(Mat& in_image, int new_width, int new_height, Mat& out_image){
    
    // some sanity checks
    // Check 1 -> new_width <= in_image.cols
    if(new_width>in_image.cols){
        cout<<"Invalid request!!! new_width has to be smaller than the current size!"<<endl;
        return false;
    }
    if(new_height>in_image.rows){
        cout<<"Invalid request!!! ne_height has to be smaller than the current size!"<<endl;
        return false;
    }
    
    if(new_width<=0){
        cout<<"Invalid request!!! new_width has to be positive!"<<endl;
        return false;
        
    }
    
    if(new_height<=0){
        cout<<"Invalid request!!! new_height has to be positive!"<<endl;
        return false;
        
    }
    cout << "endl " << endl;
    
    
    return seam_carving_trivial(in_image, new_width, new_height, out_image);
}


// seam carves by removing trivial seams
bool seam_carving_trivial(Mat& in_image, int new_width, int new_height, Mat& out_image){
    
    Mat iimage = in_image.clone();
    Mat oimage = in_image.clone();
    
    while(iimage.cols!=new_width){
        // horizontal seam if needed
        short eneryMatrix[iimage.rows][iimage.cols];
        
        int dp[iimage.rows][iimage.cols];
        //calculate energy matrix
        Vec3b z_pixel = in_image.at<Vec3b>(0,0);
        z_pixel[0] = 0;
        z_pixel[1] = 0;
        z_pixel[2] = 0;
        Vec3b l_pixel;
        Vec3b r_pixel;
        Vec3b u_pixel;
        Vec3b d_pixel;
        for (int i=0; i<iimage.rows; i++)
            for (int j=0; j<iimage.cols; j++){
                eneryMatrix[i][j] = 0;
                if (j>0)
                    l_pixel = in_image.at<Vec3b>(i,j-1);
                else
                    l_pixel = z_pixel;
                if (j<iimage.cols-1)
                    r_pixel = in_image.at<Vec3b>(i,j+1);
                else
                    r_pixel = z_pixel;
                if (i>0)
                    u_pixel = in_image.at<Vec3b>(i-1,j);
                else
                    u_pixel = z_pixel;
                if (i<iimage.rows-1)
                    d_pixel = iimage.at<Vec3b>(i+1,j);
                else
                    d_pixel = z_pixel;
                
                eneryMatrix[i][j] = eneryMatrix[i][j] + abs(r_pixel[0]-l_pixel[0]) + abs(r_pixel[1]-l_pixel[1]) + abs(r_pixel[2]-l_pixel[2]) + abs(d_pixel[0]-u_pixel[0]) + abs(d_pixel[1]-u_pixel[1]) + abs(d_pixel[2]-u_pixel[2]);
            }
        
        
        
        //        cout << "what'happending" << endl;
        if(iimage.cols>new_width){
            //calculate seam with dp
            int seam[iimage.rows];
            
            //initialization
            for (int j=0; j<iimage.cols; j++)
                dp[0][j] = eneryMatrix[0][j];
            
            //dp process
            for (int i=1; i<iimage.rows; i++)
                for (int j=0; j<iimage.cols; j++){
                    dp[i][j] = eneryMatrix[i][j];
                    if (j>0 && j<iimage.rows-1){
                        dp[i][j] += min(min(dp[i-1][j-1], dp[i-1][j]), dp[i-1][j+1]);
                    }else if (j==0){
                        dp[i][j] += min(dp[i-1][j], dp[i-1][j+1]);
                    }else{
                        dp[i][j] += min(dp[i-1][j-1], dp[i-1][j]);
                    }
                }
            
            //back trace to get the seam
            int index=-1;
            int min=INT_MAX;
            for (int j=0; j<iimage.cols; j++)
                if (dp[iimage.rows-1][j] < min){
                    min = dp[iimage.rows-1][j];
                    index = j;
                }
            seam[iimage.rows-1] = index;
            for (int i=iimage.rows-1; i>0; i--){
                int diff = dp[i][seam[i]] - eneryMatrix[i][seam[i]];
                if (seam[i]==0){
                    if (diff == dp[i-1][seam[i]])
                        seam[i-1] = seam[i];
                    else
                        seam[i-1] = seam[i]+1;
                }else if (seam[i]==iimage.cols-1){
                    if (diff == dp[i-1][seam[i]])
                        seam[i-1] = seam[i];
                    else
                        seam[i-1] = seam[i] -1 ;
                }else{
                    if (diff == dp[i-1][seam[i]-1])
                        seam[i-1] = seam[i] - 1;
                    else if (diff == dp[i-1][seam[i]])
                        seam[i-1] = seam[i];
                    else
                        seam[i-1] = seam[i] + 1;
                }
                //                cout << seam[i] << "+";
            }
            
            
            reduce_vertical_seam_trivial(iimage, oimage, seam);
            iimage = oimage.clone();
        }
        
    }
    
    while (iimage.rows!=new_height){
        // horizontal seam if needed
        short eneryMatrix[iimage.rows][iimage.cols];
        
        int dp[iimage.rows][iimage.cols];
        //calculate energy matrix
        Vec3b z_pixel = in_image.at<Vec3b>(0,0);
        z_pixel[0] = 0;
        z_pixel[1] = 0;
        z_pixel[2] = 0;
        Vec3b l_pixel;
        Vec3b r_pixel;
        Vec3b u_pixel;
        Vec3b d_pixel;
        for (int i=0; i<iimage.rows; i++)
            for (int j=0; j<iimage.cols; j++){
                eneryMatrix[i][j] = 0;
                if (j>0)
                    l_pixel = in_image.at<Vec3b>(i,j-1);
                else
                    l_pixel = z_pixel;
                if (j<iimage.cols-1)
                    r_pixel = in_image.at<Vec3b>(i,j+1);
                else
                    r_pixel = z_pixel;
                if (i>0)
                    u_pixel = in_image.at<Vec3b>(i-1,j);
                else
                    u_pixel = z_pixel;
                if (i<iimage.rows-1)
                    d_pixel = iimage.at<Vec3b>(i+1,j);
                else
                    d_pixel = z_pixel;
                
                eneryMatrix[i][j] = eneryMatrix[i][j] + abs(r_pixel[0]-l_pixel[0]) + abs(r_pixel[1]-l_pixel[1]) + abs(r_pixel[2]-l_pixel[2]) + abs(d_pixel[0]-u_pixel[0]) + abs(d_pixel[1]-u_pixel[1]) + abs(d_pixel[2]-u_pixel[2]);
            }
        
        
        
        if(iimage.rows>new_height){
            //calculate seam with dp
            int seam[iimage.cols];
            
            //initialization
            for (int i=0; i<iimage.rows; i++)
                dp[i][0] = eneryMatrix[i][0];
            
            //dp process
            for (int j=0; j<iimage.cols; j++)
                for (int i=0; i<iimage.rows; i++){
                    dp[i][j] = eneryMatrix[i][j];
                    if (i>0 && i<iimage.rows-1){
                        dp[i][j] += min(min(dp[i-1][j-1], dp[i][j-1]), dp[i+1][j-1]);
                    }else if (i==0){
                        dp[i][j] += min(dp[i][j-1], dp[i+1][j-1]);
                    }else{
                        dp[i][j] += min(dp[i-1][j-1], dp[i][j-1]);
                    }
                }
            
            //back trace to get the seam
            int index=-1;
            int min=INT_MAX;
            for (int i=0; i<iimage.rows; i++)
                if (dp[i][iimage.cols-1] < min){
                    min = dp[i][iimage.cols-1];
                    index = i;
                }
            seam[iimage.cols-1] = index;
            for (int j=iimage.cols-1; j>0; j--){
                int diff = dp[seam[j]][j] - eneryMatrix[seam[j]][j];
                if (seam[j]==0){
                    if (diff == dp[seam[j]][j-1])
                        seam[j-1] = seam[j];
                    else
                        seam[j-1] = seam[j]+1;
                }else if (seam[j]==iimage.rows-1){
                    if (diff == dp[seam[j]][j-1])
                        seam[j-1] = seam[j];
                    else
                        seam[j-1] = seam[j] -1 ;
                }else{
                    if (diff == dp[seam[j]-1][j-1])
                        seam[j-1] = seam[j] - 1;
                    else if (diff == dp[seam[j]][j-1])
                        seam[j-1] = seam[j];
                    else
                        seam[j-1] = seam[j] + 1;
                }
                //                cout << seam[i] << "+";
            }
            
            
            reduce_horizontal_seam_trivial(iimage, oimage, seam);
            iimage = oimage.clone();
        }
    }
    //        for (int i=0; i<iimage.rows; i++)
    //            for (int j=0; j<iimage.cols; j++){
    //                oimage.at<Vec3b>(i,j)[0] = eneryMatrix[i][j]/3;
    //                oimage.at<Vec3b>(i,j)[1] = eneryMatrix[i][j]/3;
    //                oimage.at<Vec3b>(i,j)[2] = eneryMatrix[i][j]/3;
    //            }
    out_image = oimage.clone();
    return true;
}

// horizontl trivial seam is a seam through the center of the image
bool reduce_horizontal_seam_trivial(Mat& in_image, Mat& out_image, int seam[]){
    
    //    retrieve the dimensions of the new image
    int rows = in_image.rows-1;
    int cols = in_image.cols;
    
    // create an image slighly smaller
    out_image = Mat(rows, cols, CV_8UC3);
    
    for(int j=0;j<cols;++j)
        for(int i=0;i<rows;++i){
            if (i<seam[j]){
                out_image.at<Vec3b>(i,j) = in_image.at<Vec3b>(i,j);
            }else{
                out_image.at<Vec3b>(i,j) = in_image.at<Vec3b>(i+1,j);
            }
            
            
            return true;
        }
}

// vertical trivial seam is a seam through the center of the image
bool reduce_vertical_seam_trivial(Mat& in_image, Mat& out_image, int seam[]){
    // retrieve the dimensions of the new image
    int rows = in_image.rows;
    int cols = in_image.cols-1;
    
    // create an image slighly smaller
    out_image = Mat(rows, cols, CV_8UC3);
    
    for(int i=0;i<rows;++i)
        for(int j=0;j<cols;++j){
            if (j<seam[i]){
                out_image.at<Vec3b>(i,j) = in_image.at<Vec3b>(i,j);
            }else{
                out_image.at<Vec3b>(i,j) = in_image.at<Vec3b>(i,j+1);
            }
            
            /* at operator is r/w
             pixel[0] --> red
             pixel[1] --> green
             pixel[2] --> blue
             */
            
            
            //            out_image.at<Vec3b>(i,j) = pixel;
        }
    
    return true;
}


