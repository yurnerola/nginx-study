package hello;

use nginx;

sub handler {
	my $r=shift;
	
	if($r->request_method eq "POST"){
		if($r->has_request_body(\&post)){
			return OK;
		}
		return OK;
	}
	
	$r->header_out("Author","Yunero");
	$r->send_http_header("text/html");
	return OK if $r->header_only;
	$r->print("\$r->header_in(\"User-Agent\"):".$r->header_in("User-Agent")."\n");
	$r->print("\$r->args:".$r->args."\n");
	$r->print("\$r->filename:".$r->filename."\n");
	$r->log_error(18, "log error from perl");
	return OK;
}

sub post{
	my $r=shift;
	$r->send_http_header;
	$r->print("request body:\"",$r->request_body,"\"\n");
	$r->print("request body file:\"",$r->request_body_file,"\"\n");
	return OK;
}

1;

__END__
