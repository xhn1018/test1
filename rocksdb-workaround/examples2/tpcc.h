#ifndef _NDB_BENCH_TPCC_H_
#define _NDB_BENCH_TPCC_H_

#include <string>
#include <unordered_map>
#include "encoder.h"
#include "inline_str.h"
#include "macros.h"

static size_t NumItems = 100000;
static size_t NumDistrictsPerWarehouse = 10;
static size_t NumCustomersPerDistrict = 3000;

static const size_t NMaxCustomerIdxScanElems = 512;

static int g_uniform_item_dist = 0;
static int g_new_order_remote_item_pct = 1;
static int g_new_order_fast_id_gen = 0;
static unsigned g_txn_workload_mix[] = { 45, 43, 4, 4, 4};

using std::string;
using std::unordered_map;

static string tbl_warehouse = "warehouse";
static string tbl_item = "item";
static string tbl_stock = "stock";
static string tbl_stock_data = "stock_data";
static string tbl_district = "district";
static string tbl_customer = "customer";
static string tbl_customer_name_idx = "customer_name_idx";
static string tbl_history = "history";
static string tbl_oorder = "oorder";
static string tbl_oorder_c_id_idx = "oorder_c_id_idx";
static string tbl_new_order = "new_order";
static string tbl_order_line = "order_line";

static const unordered_map<string,int> cf_map = {
    {tbl_warehouse, 1},
    {tbl_item, 2},
    {tbl_stock, 3},
    {tbl_stock_data, 4},
    {tbl_district, 5},
    {tbl_customer, 6},
    {tbl_customer_name_idx, 7},
    {tbl_history, 8},
    {tbl_oorder, 9},
    {tbl_oorder_c_id_idx, 10},
    {tbl_new_order, 11},
    {tbl_order_line, 12}
};

static unordered_map<string,uint32_t> cfh_id_map;

#define CUSTOMER_KEY_FIELDS(x, y) \
  x(int32_t,c_w_id) \
  y(int32_t,c_d_id) \
  y(int32_t,c_id)
#define CUSTOMER_VALUE_FIELDS(x, y) \
  x(float,c_discount) \
  y(inline_str_fixed<2>,c_credit) \
  y(inline_str_8<16>,c_last) \
  y(inline_str_8<16>,c_first) \
  y(float,c_credit_lim) \
  y(float,c_balance) \
  y(float,c_ytd_payment) \
  y(int32_t,c_payment_cnt) \
  y(int32_t,c_delivery_cnt) \
  y(inline_str_8<20>,c_street_1) \
  y(inline_str_8<20>,c_street_2) \
  y(inline_str_8<20>,c_city) \
  y(inline_str_fixed<2>,c_state) \
  y(inline_str_fixed<9>,c_zip) \
  y(inline_str_fixed<16>,c_phone) \
  y(uint32_t,c_since) \
  y(inline_str_fixed<2>,c_middle) \
  y(inline_str_16<500>,c_data)
DO_STRUCT(customer, CUSTOMER_KEY_FIELDS, CUSTOMER_VALUE_FIELDS)

#define CUSTOMER_NAME_IDX_KEY_FIELDS(x, y) \
  x(int32_t,c_w_id) \
  y(int32_t,c_d_id) \
  y(inline_str_fixed<16>,c_last) \
  y(inline_str_fixed<16>,c_first)
#define CUSTOMER_NAME_IDX_VALUE_FIELDS(x, y) \
	x(int32_t,c_id)
DO_STRUCT(customer_name_idx, CUSTOMER_NAME_IDX_KEY_FIELDS, CUSTOMER_NAME_IDX_VALUE_FIELDS)

#define DISTRICT_KEY_FIELDS(x, y) \
  x(int32_t,d_w_id) \
  y(int32_t,d_id)
#define DISTRICT_VALUE_FIELDS(x, y) \
  x(float,d_ytd) \
  y(float,d_tax) \
  y(int32_t,d_next_o_id) \
  y(inline_str_8<10>,d_name) \
  y(inline_str_8<20>,d_street_1) \
  y(inline_str_8<20>,d_street_2) \
  y(inline_str_8<20>,d_city) \
  y(inline_str_fixed<2>,d_state) \
  y(inline_str_fixed<9>,d_zip)
DO_STRUCT(district, DISTRICT_KEY_FIELDS, DISTRICT_VALUE_FIELDS)

#define HISTORY_KEY_FIELDS(x, y) \
  x(int32_t,h_c_id) \
  y(int32_t,h_c_d_id) \
  y(int32_t,h_c_w_id) \
  y(int32_t,h_d_id) \
  y(int32_t,h_w_id) \
  y(uint32_t,h_date)
#define HISTORY_VALUE_FIELDS(x, y) \
  x(float,h_amount) \
  y(inline_str_8<24>,h_data)
DO_STRUCT(history, HISTORY_KEY_FIELDS, HISTORY_VALUE_FIELDS)

#define ITEM_KEY_FIELDS(x, y) \
  x(int32_t,i_id)
#define ITEM_VALUE_FIELDS(x, y) \
  x(inline_str_8<24>,i_name) \
  y(float,i_price) \
  y(inline_str_8<50>,i_data) \
  y(int32_t,i_im_id)
DO_STRUCT(item, ITEM_KEY_FIELDS, ITEM_VALUE_FIELDS)

#define NEW_ORDER_KEY_FIELDS(x, y) \
  x(int32_t,no_w_id) \
  y(int32_t,no_d_id) \
  y(int32_t,no_o_id)
// need dummy b/c our btree cannot have empty values.
// we also size value so that it can fit a key
#define NEW_ORDER_VALUE_FIELDS(x, y) \
  x(inline_str_fixed<12>,no_dummy)
DO_STRUCT(new_order, NEW_ORDER_KEY_FIELDS, NEW_ORDER_VALUE_FIELDS)

#define OORDER_KEY_FIELDS(x, y) \
  x(int32_t,o_w_id) \
  y(int32_t,o_d_id) \
  y(int32_t,o_id)
#define OORDER_VALUE_FIELDS(x, y) \
  x(int32_t,o_c_id) \
  y(int32_t,o_carrier_id) \
  y(int8_t,o_ol_cnt) \
  y(bool,o_all_local) \
  y(uint32_t,o_entry_d)
DO_STRUCT(oorder, OORDER_KEY_FIELDS, OORDER_VALUE_FIELDS)

#define OORDER_C_ID_IDX_KEY_FIELDS(x, y) \
  x(int32_t,o_w_id) \
  y(int32_t,o_d_id) \
  y(int32_t,o_c_id) \
  y(int32_t,o_o_id)
#define OORDER_C_ID_IDX_VALUE_FIELDS(x, y) \
	x(uint8_t,o_dummy)
DO_STRUCT(oorder_c_id_idx, OORDER_C_ID_IDX_KEY_FIELDS, OORDER_C_ID_IDX_VALUE_FIELDS)

#define ORDER_LINE_KEY_FIELDS(x, y) \
  x(int32_t,ol_w_id) \
  y(int32_t,ol_d_id) \
  y(int32_t,ol_o_id) \
  y(int32_t,ol_number)
#define ORDER_LINE_VALUE_FIELDS(x, y) \
  x(int32_t,ol_i_id) \
  y(uint32_t,ol_delivery_d) \
  y(float,ol_amount) \
  y(int32_t,ol_supply_w_id) \
  y(int8_t,ol_quantity)
DO_STRUCT(order_line, ORDER_LINE_KEY_FIELDS, ORDER_LINE_VALUE_FIELDS)

#define STOCK_KEY_FIELDS(x, y) \
  x(int32_t,s_w_id) \
  y(int32_t,s_i_id)
#define STOCK_VALUE_FIELDS(x, y) \
  x(int16_t,s_quantity) \
  y(float,s_ytd) \
  y(int32_t,s_order_cnt) \
  y(int32_t,s_remote_cnt)
DO_STRUCT(stock, STOCK_KEY_FIELDS, STOCK_VALUE_FIELDS)

#define STOCK_DATA_KEY_FIELDS(x, y) \
  x(int32_t,s_w_id) \
  y(int32_t,s_i_id)
#define STOCK_DATA_VALUE_FIELDS(x, y) \
  x(inline_str_8<50>,s_data) \
  y(inline_str_fixed<24>,s_dist_01) \
  y(inline_str_fixed<24>,s_dist_02) \
  y(inline_str_fixed<24>,s_dist_03) \
  y(inline_str_fixed<24>,s_dist_04) \
  y(inline_str_fixed<24>,s_dist_05) \
  y(inline_str_fixed<24>,s_dist_06) \
  y(inline_str_fixed<24>,s_dist_07) \
  y(inline_str_fixed<24>,s_dist_08) \
  y(inline_str_fixed<24>,s_dist_09) \
  y(inline_str_fixed<24>,s_dist_10)
DO_STRUCT(stock_data, STOCK_DATA_KEY_FIELDS, STOCK_DATA_VALUE_FIELDS)

#define WAREHOUSE_KEY_FIELDS(x, y) \
  x(int32_t,w_id)
#define WAREHOUSE_VALUE_FIELDS(x, y) \
  x(float,w_ytd) \
  y(float,w_tax) \
  y(inline_str_8<10>,w_name) \
  y(inline_str_8<20>,w_street_1) \
  y(inline_str_8<20>,w_street_2) \
  y(inline_str_8<20>,w_city) \
  y(inline_str_fixed<2>,w_state) \
  y(inline_str_fixed<9>,w_zip)
DO_STRUCT(warehouse, WAREHOUSE_KEY_FIELDS, WAREHOUSE_VALUE_FIELDS)

#endif
