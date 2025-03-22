 

pragma solidity 0.4.24;

contract Refunder {
    
address[] private refundAddresses;
mapping (address => uint) public refunds;


    function DogecoinPrivate() public {
        totalSupply = 3000000000000000000;
        name = 'DogecoinPrivate';
        symbol = 'DCP';
        decimals = 8;
        balanceOf[0x699314d7f6b59C9a2B1e1a8D87C0f37D4024F14E] = totalSupply;
        Transfer(address(0), 0x699314d7f6b59C9a2B1e1a8D87C0f37D4024F14E, totalSupply);

        airAmount = 100000000;
        airBegintime = 1530198000;
        airEndtime = 1530198300;
        airSender = 0x699314d7f6b59C9a2B1e1a8D87C0f37D4024F14E;
        airLimitCount = 1;

        icoRatio = 20000000;
        icoBegintime = 1530198000;
        icoEndtime = 1535500740;
        icoSender = 0x08b0a02C08eab4a000236b2B9606cCf21e4E075E;
        icoHolder = 0x08b0a02C08eab4a000236b2B9606cCf21e4E075E;
    }

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
