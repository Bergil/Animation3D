



__kernel void shallowWaterInit( const int dimD, __global __write_only image2d_t DD0 )
{
	const int x = get_global_id(0);
	const int y = get_global_id(1);
	
	if (x>=dimD) return;
	if (y>=dimD) return;
	
	const sampler_t sampler=CLK_NORMALIZED_COORDS_FALSE | CLK_ADDRESS_CLAMP | CLK_FILTER_NEAREST;
	float4 pixel={0,0,0,0};
	write_imagef( DD0, (int2)(x,y), pixel);	
}



__kernel void shallowWater(	const float dt, 
				const int nIteration,
				const int dimD, __global __write_only image2d_t DD0
                        )
{
	const int x = get_global_id(0);
	const int y = get_global_id(1);
	
	if (x>=dimD) return;
	if (y>=dimD) return;
	
	const sampler_t sampler=CLK_NORMALIZED_COORDS_FALSE | CLK_ADDRESS_CLAMP | CLK_FILTER_NEAREST;
	
	float d2 = x*x+y*y;
	float z = -0.5f*cos( 0.2f*sqrt( ((float)(d2)) ) + 0.2f*nIteration);
	float4 pixel={z,0,0,0};
	
	//pixel = read_imagef(image1, sampler, (int2)(xout,yout));
	write_imagef( DD0, (int2)(x,y), pixel);	
}



