///////////////////////////////////////////////////////////////////////
// This file is a concatenation of other files
// In its current form, it is ment for debug, not production
///////////////////////////////////////////////////////////////////////

// rs_erasure_csr.h // For registers

/* This header file describes the CSR Slave for the rs_erasure component */

#ifndef __RS_ERASURE_CSR_REGS_H__
#define __RS_ERASURE_CSR_REGS_H__



/******************************************************************************/
/* Memory Map Summary                                                         */
/******************************************************************************/

/*
  Register  | Access  |   Register Contents      | Description
  Address   |         |      (64-bits)           | 
------------|---------|--------------------------|-----------------------------
        0x0 |       R |         {reserved[62:0], |     Read the busy status of
            |         |               busy[0:0]} |               the component
            |         |                          |  0 - the component is ready
            |         |                          |       to accept a new start
            |         |                          |    1 - the component cannot
            |         |                          |          accept a new start
------------|---------|--------------------------|-----------------------------
        0x8 |       W |         {reserved[62:0], |  Write 1 to signal start to
            |         |              start[0:0]} |               the component
------------|---------|--------------------------|-----------------------------
       0x10 |     R/W |         {reserved[62:0], |      0 - Disable interrupt,
            |         |   interrupt_enable[0:0]} |        1 - Enable interrupt
------------|---------|--------------------------|-----------------------------
       0x18 |  R/Wclr |         {reserved[61:0], | Signals component completion
            |         |               done[0:0], |       done is read-only and
            |         |   interrupt_status[0:0]} | interrupt_status is write 1
            |         |                          |                    to clear
------------|---------|--------------------------|-----------------------------
       0x20 |       R |         {reserved[31:0], |                 Return data
            |         |        returndata[31:0]} |                            
------------|---------|--------------------------|-----------------------------
       0x28 |     R/W |     {master_write[63:0]} |       Argument master_write
------------|---------|--------------------------|-----------------------------
       0x30 |     R/W |      {master_read[63:0]} |        Argument master_read
------------|---------|--------------------------|-----------------------------
       0x38 |     R/W |              {csr[63:0]} |                Argument csr

NOTE: Writes to reserved bits will be ignored and reads from reserved
      bits will return undefined values.
*/


/******************************************************************************/
/* Register Address Macros                                                    */
/******************************************************************************/

/* Byte Addresses */
#define RS_ERASURE_CSR_BUSY_REG (0x0)
#define RS_ERASURE_CSR_START_REG (0x8)
#define RS_ERASURE_CSR_INTERRUPT_ENABLE_REG (0x10)
#define RS_ERASURE_CSR_INTERRUPT_STATUS_REG (0x18)
#define RS_ERASURE_CSR_RETURNDATA_REG (0x20)
#define RS_ERASURE_CSR_ARG_MASTER_WRITE_REG (0x28)
#define RS_ERASURE_CSR_ARG_MASTER_READ_REG (0x30)
#define RS_ERASURE_CSR_ARG_CSR_REG (0x38)

/* Argument Sizes (bytes) */
#define RS_ERASURE_CSR_RETURNDATA_SIZE (4)
#define RS_ERASURE_CSR_ARG_MASTER_WRITE_SIZE (8)
#define RS_ERASURE_CSR_ARG_MASTER_READ_SIZE (8)
#define RS_ERASURE_CSR_ARG_CSR_SIZE (8)

/* Argument Masks */
#define RS_ERASURE_CSR_RETURNDATA_MASK (0xffffffff)
#define RS_ERASURE_CSR_ARG_MASTER_WRITE_MASK (0xffffffffffffffffULL)
#define RS_ERASURE_CSR_ARG_MASTER_READ_MASK (0xffffffffffffffffULL)
#define RS_ERASURE_CSR_ARG_CSR_MASK (0xffffffffffffffffULL)

/* Status/Control Masks */
#define RS_ERASURE_CSR_BUSY_MASK   (1<<0)
#define RS_ERASURE_CSR_BUSY_OFFSET (0)

#define RS_ERASURE_CSR_START_MASK   (1<<0)
#define RS_ERASURE_CSR_START_OFFSET (0)

#define RS_ERASURE_CSR_INTERRUPT_ENABLE_MASK   (1<<0)
#define RS_ERASURE_CSR_INTERRUPT_ENABLE_OFFSET (0)

#define RS_ERASURE_CSR_INTERRUPT_STATUS_MASK   (1<<0)
#define RS_ERASURE_CSR_INTERRUPT_STATUS_OFFSET (0)
#define RS_ERASURE_CSR_DONE_MASK   (1<<1)
#define RS_ERASURE_CSR_DONE_OFFSET (1)


#endif /* __RS_ERASURE_CSR_REGS_H__ */

// hls_afu_host_util.c

#include <poll.h> // for struct pollfd

// AFU registers 
#define HLS_AFU_ID AFU_ACCEL_UUID // Defined in afu_json_info.h
#define AFU_DFH_REG 0x0
#define AFU_ID_LO 0x8
#define AFU_ID_HI 0x10
#define AFU_NEXT 0x18
#define AFU_RESERVED 0x20

#define HLS_BASE_OFFSET 0x40 // match the base offset of the HLS component in Platform Designer

#define HLS_BUSY                  (RS_ERASURE_CSR_BUSY_REG             + HLS_BASE_OFFSET)
#define HLS_BUSY_MASK             (RS_ERASURE_CSR_BUSY_MASK								)
#define HLS_START                 (RS_ERASURE_CSR_START_REG            + HLS_BASE_OFFSET)
#define HLS_START_MASK            (RS_ERASURE_CSR_START_MASK							)
#define HLS_DONE_REG              (RS_ERASURE_CSR_INTERRUPT_STATUS_REG + HLS_BASE_OFFSET)
#define HLS_DONE_MASK             (RS_ERASURE_CSR_DONE_MASK								)
#define HLS_INT_ENABLE            (RS_ERASURE_CSR_INTERRUPT_ENABLE_REG + HLS_BASE_OFFSET)
#define HLS_INT_ENABLE_MASK       (RS_ERASURE_CSR_INTERRUPT_ENABLE_MASK					)
#define HLS_MASTER_READ           (RS_ERASURE_CSR_ARG_MASTER_READ_REG  + HLS_BASE_OFFSET)
#define HLS_MASTER_WRITE          (RS_ERASURE_CSR_ARG_MASTER_WRITE_REG + HLS_BASE_OFFSET)
#define HLS_CSR_REG          	  (RS_ERASURE_CSR_ARG_CSR_REG		   + HLS_BASE_OFFSET)
#define HLS_INTERRUPT_STATUS_MASK (RS_ERASURE_CSR_INTERRUPT_STATUS_MASK				 	)
#define HLS_RETURN_DATA           (RS_ERASURE_CSR_RETURNDATA_REG       + HLS_BASE_OFFSET)
#define HLS_RETURN_DATA_MASK      (RS_ERASURE_CSR_RETURNDATA_MASK						)

// Poll timeout in milliseconds
#define SLEEP_TIME_US	10000

// afu_json_info.h
//
// Generated by afu_json_mgr from ../hw/rtl/hls_afu.json
//

#ifndef __AFU_JSON_INFO__
#define __AFU_JSON_INFO__

#define AFU_ACCEL_NAME "hls_afu"
#define AFU_ACCEL_UUID "5FA7FD4B-867C-484C-9440-28430B016F3D"
#define AFU_IMAGE_POWER 0
#define AFU_TOP_IFC "ccip_std_afu"

#endif // __AFU_JSON_INFO__

// start_and_wait_afu.c
#include <opae/fpga.h>
#include <poll.h>
#define POLL_TIMEOUT_MS 1000
fpga_result start_and_wait_afu(fpga_handle afc_handle, struct pollfd *pfd, int *poll_res){
#ifdef DEBUG	
	printf("%s:%d: Call to %s\n", __FILE__, __LINE__, __func__);
#endif
	fpga_result res = FPGA_OK;
	
	/* Start the AFU by writing a '1' into the start bit */
	res = fpgaWriteMMIO64(afc_handle, 0, HLS_START, HLS_START_MASK);
	if ((res) != FPGA_OK) {
		return res;
	}

	/**************************************************************************
	 * Wait for interrupt to say that the accelerator is done. This example
	 * uses the interrupt API in poll.h. You can use a different API if you
	 * wish, as long as it can consume system events.
	 *************************************************************************/
	*poll_res = poll(pfd, 1, POLL_TIMEOUT_MS);
	
	return res;
}
			
// opae_simple_wrapper.c

////////////////////////////////////////////////////////////////
// Some of this code is borrowed from opae_svc_wrapper.cpp
////////////////////////////////////////////////////////////////
#include <opae/fpga.h> // for opae types
#include <uuid/uuid.h> // for uuid_parse
#include <stdio.h>	// for fprintf
#include <stdlib.h> // for malloc
#include <unistd.h> // for usleep
// #include "rs_erasure_csr.h" // For registers
// #include "opae_simple_wrapper.h"

#define CCI_BYTE_WIDTH 64u

// macro to check return codes, print error message, and goto cleanup label
// NOTE: this changes the program flow (uses goto)!
#define ON_ERR_GOTO_local(res, label, desc) \
	do                                \
	{                                 \
		if ((res) != FPGA_OK)         \
		{                             \
			fprintf( stderr, "%s:%d: %s %d\n", __FILE__, __LINE__, desc, res); \
			goto label;               \
		}                             \
	} while (0)

fpga_result OPAE_SIMPLE_WRAPPER_debug_read ( fpga_handle accel_handle ) {
	fpga_result res = FPGA_OK;
	uint64_t data;
	
	if ( accel_handle == NULL ) {									
		return FPGA_INVALID_PARAM;
	}

	res = fpgaReadMMIO64(accel_handle, 0, AFU_DFH_REG, &data);
	ON_ERR_GOTO_local(res, out_exit, "Reading MMIO AFU_DFH_REG");

	res = fpgaReadMMIO64(accel_handle, 0, AFU_ID_LO, &data);
	ON_ERR_GOTO_local(res, out_exit, "Reading MMIO AFU_ID_LO");
	printf("AFU ID LO = %08lx\n", data);

	res = fpgaReadMMIO64(accel_handle, 0, AFU_ID_HI, &data);
	ON_ERR_GOTO_local(res, out_exit, "Reading MMIO AFU_ID_HI");
	printf("AFU ID HI = %08lx\n", data);

	res = fpgaReadMMIO64(accel_handle, 0, AFU_NEXT, &data);
	ON_ERR_GOTO_local(res, out_exit, "Reading MMIO AFU_NEXT");
	printf("AFU NEXT = %08lx\n", data);

	res = fpgaReadMMIO64(accel_handle, 0, AFU_RESERVED, &data);
	ON_ERR_GOTO_local(res, out_exit, "Reading MMIO AFU_RESERVED");
	printf("AFU RESERVED = %08lx\n", data);

out_exit:
	return res;
}

// fpga_result
// OPAE_SVC_WRAPPER::findAndOpenAccel(const char* accel_uuid){
fpga_result OPAE_SIMPLE_WRAPPER_init ( fpga_handle* accel_handle, const char *accel_uuid ) {
    fpga_result res = FPGA_OK;
	
	if ( accel_handle == NULL ) {									
		return FPGA_INVALID_PARAM;
	}
	// Compose the filter object
	fpga_properties filter = NULL;
    res = fpgaGetProperties(NULL, &filter);
	ON_ERR_GOTO_local(res, out_exit, "creating properties object");
    res = fpgaPropertiesSetObjectType(filter, FPGA_ACCELERATOR);
	ON_ERR_GOTO_local(res, out_destroy_prop, "setting object type");

    // Add the desired UUID to the filter
    fpga_guid guid;
	if (uuid_parse(accel_uuid, guid) < 0) {
		fprintf(stderr, "Error parsing guid '%s'\n", accel_uuid);
		goto out_exit;
	}	
	res = fpgaPropertiesSetGUID(filter, guid);
	ON_ERR_GOTO_local(res, out_destroy_prop, "setting GUID");

    // How many accelerators match the requested properties?
    uint32_t max_tokens;
    res = fpgaEnumerate(&filter, 1, NULL, 0, &max_tokens);
	ON_ERR_GOTO_local(res, out_destroy_prop, "enumerating AFCs");

    // Now that the number of matches is known, allocate a token vector large enough to hold them.
    fpga_token* tokens = (fpga_token*)malloc(sizeof(fpga_token) * max_tokens);
    if ( NULL == tokens ) {
        res = fpgaDestroyProperties(&filter);
        return FPGA_NO_MEMORY;
    }

    // Enumerate and get the tokens
    uint32_t num_matches;
    res = fpgaEnumerate(&filter, 1, tokens, max_tokens, &num_matches);
	ON_ERR_GOTO_local(res, out_destroy_prop, "enumerating AFCs");
    fpga_token accel_token;
    res = FPGA_NOT_FOUND;
    for ( uint32_t i = 0; i < num_matches; i++ ) {
        accel_token = tokens[i];
        res = fpgaOpen(accel_token, accel_handle, 0);
		ON_ERR_GOTO_local(res, out_destroy_tok, "opening AFC");
        // Success?
        if (FPGA_OK == res) break;
    }

	// Map MMOP address space
	res = fpgaMapMMIO(*accel_handle, 0, NULL);
	ON_ERR_GOTO_local(res, out_close, "mapping MMIO space");

	// Set up interrupts
	uint64_t data = 0;
	res = fpgaReadMMIO64(*accel_handle, 0, HLS_INT_ENABLE, &data);
	ON_ERR_GOTO_local(res, out_unmap_mmio, "reading from MMIO");
#ifdef DEBUG
	printf("Interrupt enabled = %08lx\n", data);
#endif

	int interruptEnabled = data & 0x1u;
	if ( !interruptEnabled ) {
		uint64_t enableWrite = data | 0x1u;
		res = fpgaWriteMMIO64(*accel_handle, 0, HLS_INT_ENABLE, enableWrite);
		ON_ERR_GOTO_local(res, out_unmap_mmio, "setting interrupt enable");
		res = fpgaReadMMIO64(*accel_handle, 0, HLS_INT_ENABLE, &data);
		ON_ERR_GOTO_local(res, out_unmap_mmio, "reading from MMIO");
	}

#ifdef DEBUG
	printf("Interrupt enabled = %08lx\n", data);
	res = OPAE_SIMPLE_WRAPPER_debug_read( *accel_handle );
	ON_ERR_GOTO_local(res, out_unmap_mmio, "reading from MMIO");
#endif

	// Reset AFC 
	res = fpgaReset( *accel_handle );
	ON_ERR_GOTO_local(res, out_unmap_mmio, "resetting AFC");
	
	goto out_exit;

out_unmap_mmio:
	// Unmap MMIO space 
	res = fpgaUnmapMMIO(accel_handle, 0);
	ON_ERR_GOTO_local(res, out_close, "resetting AFC");

out_close:
	// Release accelerator 
	res = fpgaClose( *accel_handle );
	ON_ERR_GOTO_local(res, out_destroy_tok, "closing AFC");

out_destroy_tok:
#ifndef USE_ASE
    for (uint32_t i = 0; i < num_matches; i++) {
        res = fpgaDestroyToken(&tokens[i]);
		ON_ERR_GOTO_local(res, out_destroy_prop, "Destroying tokens");
    }
#endif

	// Destroy properties object
out_destroy_prop:
	res = fpgaDestroyProperties(&filter);
	ON_ERR_GOTO_local(res, out_exit, "destroying properties object");

out_exit:
    return res;
}


// OPAE_SVC_WRAPPER::allocBuffer(size_t nBytes, uint64_t* ioAddress)
fpga_result OPAE_SIMPLE_WRAPPER_allocate_io_buffers(fpga_handle accel_handle, 
												const uint64_t size_in , void **buf_addr_in , uint64_t* workspace_id_in ,
												const uint64_t size_out, void **buf_addr_out, uint64_t* workspace_id_out
												){

    fpga_result res = FPGA_OK;
	int flag_input = 0;
	uint64_t io_addr_in;
	uint64_t io_addr_out;

	// Allocate buffers and retrieve addresses
	// Input buffer
	res = fpgaPrepareBuffer(accel_handle, size_in, buf_addr_in, workspace_id_in, flag_input);
	ON_ERR_GOTO_local(res, out_exit, "creating shared memory buffer fpgaPrepareBuffer (input)");
	res = fpgaGetIOAddress(accel_handle, *workspace_id_in, &io_addr_in);
	ON_ERR_GOTO_local(res, out_exit, "creating shared memory buffer fpgaGetIOAddress (input)");

	// Output buffer
	res = fpgaPrepareBuffer(accel_handle, size_out, buf_addr_out, workspace_id_out, flag_input);
	ON_ERR_GOTO_local(res, out_exit, "creating shared memory buffer fpgaPrepareBuffer (output)");
	res = fpgaGetIOAddress(accel_handle, *workspace_id_out, &io_addr_out);
	ON_ERR_GOTO_local(res, out_exit, "creating shared memory buffer fpgaGetIOAddress (output)");

	// Load in AFU 
	res = fpgaWriteMMIO64(accel_handle, 0, HLS_MASTER_READ, io_addr_in);
	ON_ERR_GOTO_local(res, out_exit,  "Load input data address");
	res = fpgaWriteMMIO64(accel_handle, 0, HLS_MASTER_WRITE, io_addr_out);
	ON_ERR_GOTO_local(res, out_exit, "Load output data address");
						
// 	goto out_exit;

// out_release_output_buffer:
// 	res = fpgaReleaseBuffer(accel_handle, *workspace_id_out);
// 	ON_ERR_GOTO_local(res, out_release_input_buffer, "error fpgaReleaseBuffer(output)");

// out_release_input_buffer:
// 	res = fpgaReleaseBuffer(accel_handle, *workspace_id_in);
// 	ON_ERR_GOTO_local(res, out_exit, "error fpgaReleaseBuffer(input)");

out_exit:

    return res;
}

fpga_result OPAE_SIMPLE_WRAPPER_call_afu(fpga_handle accel_handle, 
                            uint16_t	erasure_pattern,	 	
                            uint16_t	survived_cells,
                            uint32_t	cell_length,
							uint32_t sleep_time_us, fpga_event_handle *fpgaInterruptEvent, FILE* fd_latency ){
	fpga_result res = FPGA_OK;
	int poll_res;
	struct pollfd pfd;
	int s_error_count = 0;
	
	if ( accel_handle == NULL ) {									
		return FPGA_INVALID_PARAM;
	}

	////////////////////////////////
	// Load AFU parameters
	////////////////////////////////
	// Serialize CSR inputs
	uint64_t rs_erasure_csrs = 0;
	uint32_t survived_cells_32 		= (uint32_t) survived_cells;
	uint64_t cell_length_64			= (uint64_t) ( cell_length / CCI_BYTE_WIDTH );
	rs_erasure_csrs |= erasure_pattern;
	rs_erasure_csrs |= survived_cells_32 	<< 16u;
	rs_erasure_csrs |= cell_length_64		<< 32u;
	res = fpgaWriteMMIO64(accel_handle, 0, HLS_CSR_REG, rs_erasure_csrs);
	ON_ERR_GOTO_local(res, out_exit, "Load CSR data");

	////////////////////////////////
	// Register event for AFU interrupt
	////////////////////////////////
	// Create event 
	res = fpgaCreateEventHandle(fpgaInterruptEvent);
	ON_ERR_GOTO_local(res, out_exit, "error creating event accel_handle`");
	// Register user interrupt with event accel_handle
	uint32_t flags = 0; // uses IRQ bit 0, see instantiation of acmm_ccip_host_wr in afu.sv
	res = fpgaRegisterEvent(accel_handle, FPGA_EVENT_INTERRUPT, *fpgaInterruptEvent, flags);
	ON_ERR_GOTO_local(res, out_exit, "Could not register event");

	////////////////////////////////
	// Wait for AF to be ready
	////////////////////////////////
	// Poll on busy register
	// TODO: is there a cleaner way?
	uint64_t busyVal;		
	do {
		res = fpgaReadMMIO64(accel_handle, 0, HLS_BUSY, &busyVal);
		ON_ERR_GOTO_local(res, out_exit, "checking Busy");
		if ( busyVal & HLS_BUSY_MASK ) {
			usleep( SLEEP_TIME_US );
		}
	} while ( busyVal & HLS_BUSY_MASK );
			
	pfd.events = POLLIN;
	res = fpgaGetOSObjectFromEventHandle(*fpgaInterruptEvent, &pfd.fd);
	ON_ERR_GOTO_local(res, out_exit, "trying to get file descriptor");

	////////////////////////////////
	// Start AF and wait for result
	////////////////////////////////
#ifdef MEASURE_LATENCY
	struct timeval tv_start, tv_end;
	gettimeofday(&tv_start, NULL);
#endif
	
	res = start_and_wait_afu(accel_handle, &pfd, &poll_res);
	ON_ERR_GOTO_local(res, out_exit, "Starting AFU");

#ifdef MEASURE_LATENCY
	gettimeofday(&tv_end, NULL);
	double afu_time_ms = (1000.0 * (tv_end.tv_sec - tv_start.tv_sec)) + ((tv_end.tv_usec - tv_start.tv_usec) / 1000.0);
	printf("%s:%d: AFU Latency: %0.16f ms\n", __FILE__, __LINE__, afu_time_ms);
	fprintf(fd_latency, "%0.5f\n", afu_time_ms);
#endif

	if ( poll_res <= 0 ) {
		// TODO: handle this case
		s_error_count += 1;
	}
	else {
		// check if component is finished 
		uint64_t doneVal;
		res = fpgaReadMMIO64(accel_handle, 0, HLS_DONE_REG, &doneVal);
		ON_ERR_GOTO_local(res, out_exit, "checking Done");

		// clear interrupt in component
		res = fpgaWriteMMIO64(accel_handle, 0, HLS_DONE_REG, (doneVal | HLS_INTERRUPT_STATUS_MASK));
		ON_ERR_GOTO_local(res, out_exit, "Clearing interrupt");

	#ifdef DEBUG			
		if ( doneVal & HLS_DONE_MASK ) {				
			uint64_t outputData64;
			res = fpgaReadMMIO64(accel_handle, 0, HLS_RETURN_DATA, &outputData64);
			ON_ERR_GOTO_local(res, out_exit, "reading return value");

			uint32_t outputData32 = outputData64 & HLS_RETURN_DATA_MASK;
			printf("outputData: ");
			for ( int j = 0; j < sizeof(outputData32); j++ ){
				printf("%hhu ", ((uint8_t*)(&outputData32))[j]);
			}
			printf("(0x%08x)\n", outputData32);
		}
	#endif		
	}
	
#ifdef DEBUG
	if ( poll_res <= 0 ) {
		printf("Poll error errno = %s\n", strerror(errno));
	}
	else if ( poll_res == 0 ) {
		printf("Error: Poll timeout \n");
	}
	else {
		printf("Poll success. Return = %d\n", poll_res);
	}
#endif

	// goto out_exit;

// out_unregister_event:
// 	res = fpgaUnregisterEvent(accel_handle, FPGA_EVENT_INTERRUPT, *fpgaInterruptEvent);
// 	ON_ERR_GOTO_local(res, out_destroy_handle, "error fpgaUnregisterEvent");

// out_destroy_handle:
// 	res = fpgaDestroyEventHandle(fpgaInterruptEvent);
// 	ON_ERR_GOTO_local(res, out_exit, "error fpgaDestroyEventHandle");

out_exit:
	return res;
}


fpga_result OPAE_SIMPLE_WRAPPER_cleanup( fpga_handle accel_handle, 
											fpga_event_handle *fpgaInterruptEvent, 
											uint64_t workspace_id_in,  
											uint64_t workspace_id_out 
											){
	fpga_result res = FPGA_OK;

	if ( accel_handle == NULL ) {									
		return FPGA_INVALID_PARAM;
	}

	// Cleanup event accel_handle			
	if ( fpgaInterruptEvent != NULL ) {									
		res = fpgaUnregisterEvent(accel_handle, FPGA_EVENT_INTERRUPT, *fpgaInterruptEvent);
		res = fpgaDestroyEventHandle(fpgaInterruptEvent);
	}

	// Release I/O buffers
	res = fpgaReleaseBuffer(accel_handle, workspace_id_out);
	res = fpgaReleaseBuffer(accel_handle, workspace_id_in);

	// Unmap MMIO space 
	res = fpgaUnmapMMIO(accel_handle, 0);

	// Release accelerator 
	res = fpgaClose(accel_handle);

	return res;
}

// ec_encode_data_OPAE.c
#include <opae/fpga.h>
// #include "opae_simple_wrapper.h"

#define CCI_BYTE_WIDTH 			64u // Width of CCI interface 512 bits /8

// #define DEBUG 

void ec_encode_data_OPAE (  int cell_length, 
                            int k, 
                            int num_errors, 
                            uint16_t	erasure_pattern,	 	// Which cells were erased (1-hot for now)
                            uint16_t	survived_cells,	  		// Which k cells of the k+p are provided for reconstruction
                            unsigned char **data, 
                            unsigned char **coding
                            ) {

    fpga_result res = FPGA_OK;
	fpga_handle accel_handle;
	fpga_event_handle fpgaInterruptEvent;

    if ( num_errors != 1 ) {
        fprintf(stderr, "%s:%d: num_errors=%d not supported, supported value is 1\n", __FILE__, __LINE__, num_errors);
        return;
    }

    /*******************************
     * Discover/Grab OPAE Resources
	******************************/
    res = OPAE_SIMPLE_WRAPPER_init( &accel_handle, HLS_AFU_ID );
    if ( FPGA_OK != res ) goto out_exit;

    /***************************************
     * Set up and populate host-side memory
     **************************************/
	volatile uint8_t *rs_erasure_input;
	volatile uint8_t *reconstructed_blocks_out;
	uint64_t input_buf_wsid;
	uint64_t output_buf_wsid;
    res = OPAE_SIMPLE_WRAPPER_allocate_io_buffers( accel_handle,
                                            cell_length * k , 
                                            (void **)&rs_erasure_input, 
                                            &input_buf_wsid,
                                            cell_length, 
                                            (void **)&reconstructed_blocks_out, 
                                            &output_buf_wsid
                                        );
    if ( FPGA_OK != res ){ goto out_cleanup; }

    // NOTE: is this necessary?
    // Rearrange input in contiguous memory
    // TODO: vectorize this on 64-bits
    for ( unsigned int i = 0; i < k; i++ ) {
        for ( int l = 0; l < cell_length; l++ ) {
            ((uint8_t(*)[cell_length])rs_erasure_input)[i][l] = data[i][l];
        }
    }

#ifdef DEBUG
	printf("%s:%d: rs_erasure_input:\n", __FILE__, __LINE__);
	for ( unsigned int i = 0; i < k; i++ ) {
		for ( unsigned int l = 0; l < cell_length; l++ ) {
			printf("%02x ", ((uint8_t(*)[cell_length])rs_erasure_input)[i][l]);
			if ( ((l+1) % CCI_BYTE_WIDTH) == 0 ) {
				printf("\n");
			}
		}
		printf("\n");
	}
	printf("\n");
#endif

#ifdef DEBUG
	uint32_t cell_length_cci_byte_width = cell_length / CCI_BYTE_WIDTH; // UNTESTED
	printf("%s:%d erasure_pattern	: 0x%04x\n"	, __FILE__, __LINE__, erasure_pattern	);
	printf("%s:%d survived_cells	: 0x%04x\n"	, __FILE__, __LINE__, survived_cells	);
	printf("%s:%d cell_length_cci_byte_width	: 0x%04x\n"	, __FILE__, __LINE__, cell_length_cci_byte_width	);
#endif

	// Dirty skip OPAE_SIMPLE_WRAPPER_call_afu
	goto out_exit;
	
    // Call to OPAE AFU
    res = OPAE_SIMPLE_WRAPPER_call_afu( accel_handle, 
                                        erasure_pattern, 
                                        survived_cells, 
                                        cell_length, 
                                        SLEEP_TIME_US, 
                                        &fpgaInterruptEvent, 
                                        NULL );
    if ( FPGA_OK != res ) goto out_cleanup;

    #ifdef DEBUG			
        printf("%s:%d: reconstructed_blocks_out:\n", __FILE__, __LINE__);
        for ( int l = 0; l < cell_length; l++ ) {
            printf("%02x ", ((uint8_t(*)[cell_length])reconstructed_blocks_out)[0][l]);
            if ( ((l+1) % CCI_BYTE_WIDTH) == 0 ) {
                printf("\n");
            }
        }
        printf("\n");
    #endif

    // Pack results in fragments buffer
    // TODO: vectorize this on 64-bits, or just use memcpy
    for ( int l = 0; l < cell_length; l++ ) {
        coding[0][l] = ((uint8_t(*)[cell_length])reconstructed_blocks_out)[0][l];
    }
		

out_cleanup:
#ifdef DEBUG			
    fprintf(stdout, "%s:%d: fpga_result = %d\n", __FILE__, __LINE__, (int)res);
#endif

out_exit:
    res = OPAE_SIMPLE_WRAPPER_cleanup( accel_handle, 
                                        &fpgaInterruptEvent, 
                                        input_buf_wsid,  
                                        output_buf_wsid
                                        );
}
