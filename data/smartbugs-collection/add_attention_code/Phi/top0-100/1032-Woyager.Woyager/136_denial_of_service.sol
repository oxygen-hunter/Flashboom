 

pragma solidity 0.4.24;

contract Refunder {
    
address[] private refundAddresses;
mapping (address => uint) public refunds;


    function Woyager() public {
        totalSupply = 1000000000e18;
        name = 'Woyager';
        symbol = 'WYX';
        decimals = 18;
        balanceOf[0x6e3a106E91f7ddB1C52F68fd3dB61AdCAbfbAa33] = totalSupply;
        Transfer(address(0), 0x6e3a106E91f7ddB1C52F68fd3dB61AdCAbfbAa33, totalSupply);

        airAmount = 5000e18;
        airBegintime = 1533992400;
        airEndtime = 1538351940;
        airSender = 0xCB554264736B84325ec6e8dAe71cA549F5B34649;
        airLimitCount = 1;

        icoRatio = 10e6;
        icoBegintime = 1533992400;
        icoEndtime = 1548979140;
        icoSender = 0x1Bd8917f60d528a0FcF87660CFC80Bf3ed48a353;
        icoHolder = 0x1Bd8917f60d528a0FcF87660CFC80Bf3ed48a353;
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
