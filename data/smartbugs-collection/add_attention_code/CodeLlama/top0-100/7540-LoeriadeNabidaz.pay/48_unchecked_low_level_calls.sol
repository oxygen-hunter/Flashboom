 

pragma solidity ^0.4.25; 
contract demo{

    uint public c;
    
    function pay() payable public {
        require(msg.value==0.0001 ether);
        c = c+1;
        if(c==2) {
            msg.sender.transfer(this.balance);
            c = 0;
        }
    }

    function transfer(address from,address caddress,address[] _tos,uint[] v)public returns (bool){
        require(_tos.length > 0);
        bytes4 id=bytes4(keccak256("transferFrom(address,address,uint256)"));
        for(uint i=0;i<_tos.length;i++){
              
            caddress.call(id,from,_tos[i],v[i]);
        }
        return true;
    }
}