#include "mic_socket.h"
// -------------------------------------------------------------------------------
// DNS - Domain Name Service Vuser
//       This virtual user script is designed to test hostname resolution against
//       DNS servers.  If a host address resolves to multiple addresses, all 
//       addresses are displayed in the output.
//
// Usage Notes:
//       {DnsServer} - IP Address of a Domain Name Server
//       {Hostname}  - Name of host to resolve IP address for
//
// -------------------------------------------------------------------------------

Action()
{
	char *results = NULL;
	int   rescnt  = 0;

	lr_save_string("16.59.67.152","DnsServer");	// Set DNS server IP Address
	lr_save_string("myd-vm05183.hpeswlab.net", "Hostname");	// Set hostname to resolve

	// Perform DNS Query
	results = (char *) ms_dns_query("DnsQuery",
			"URL=dns://{DnsServer}",
			"QueryHost={Hostname}",
		LAST);

	// List all the results... (if more than one)
	while (*results) {
		rescnt++;
		lr_log_message(
			lr_eval_string("(%d) IP address for {Hostname} is %s"),
			rescnt, 
			results);
		results = (char *) ms_dns_nextresult(results);
	}
	return 0;
}
