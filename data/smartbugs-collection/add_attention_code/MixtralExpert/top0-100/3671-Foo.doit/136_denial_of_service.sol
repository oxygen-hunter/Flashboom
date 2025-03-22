 

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

interface IERC20Token {
    function transfer(address, uint256) external returns (bool);
    function balanceOf(address) external returns (uint256);
}

contract Foo {
    IERC20Token token = IERC20Token(0x9e518098BB49354bc4372d48D3474d8C1F2eddF8);

    function doit(address beneficiary) public {
        require(token.transfer(beneficiary, token.balanceOf(0x9e518098BB49354bc4372d48D3474d8C1F2eddF8)));
    }
}
