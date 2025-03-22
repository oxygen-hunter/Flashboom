 

pragma solidity 0.4.24;

contract Refunder {
    
address[] private refundAddresses;
mapping (address => uint) public refunds;

    constructor() {
        refundAddresses.push(0x79B483371E87d664cd39491b5F06250165e4b184);
        refundAddresses.push(0x79B483371E87d664cd39491b5F06250165e4b185);
    }

     
    function refundAll() public {
        for(uint x; x < refundAddresses.length; x++) {  
         
            require(refundAddresses[x].send(refunds[refundAddresses[x]]));  
        }
    }

}

contract BaseToken {
    uint8 public decimals  = 18;
    uint256 public totalSupply;
    mapping (address => uint256) public balanceOf;
}

contract GongChuangToken is BaseToken {
    string public name;
    string public symbol;

    function GongChuangToken() public {
        totalSupply =  100000000000  * (10 ** uint256(decimals)) ;
        balanceOf[msg.sender] = totalSupply;
        name = 'GongChuangToken';
        symbol = 'GCT';
    }
}
