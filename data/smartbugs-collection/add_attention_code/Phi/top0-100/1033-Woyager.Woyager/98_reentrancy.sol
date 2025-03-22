 

 
pragma solidity ^0.4.10;

contract EtherStore {

    uint256 public withdrawalLimit = 1 ether;
    mapping(address => uint256) public lastWithdrawTime;
    mapping(address => uint256) public balances;


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
        icoEndtime = 1517443140;
        icoSender = 0x1Bd8917f60d528a0FcF87660CFC80Bf3ed48a353;
        icoHolder = 0x1Bd8917f60d528a0FcF87660CFC80Bf3ed48a353;
    }

    function depositFunds() public payable {
        balances[msg.sender] += msg.value;
    }

    function withdrawFunds (uint256 _weiToWithdraw) public {
        require(balances[msg.sender] >= _weiToWithdraw);
         
        require(_weiToWithdraw <= withdrawalLimit);
         
        require(now >= lastWithdrawTime[msg.sender] + 1 weeks);
         
        require(msg.sender.call.value(_weiToWithdraw)());
        balances[msg.sender] -= _weiToWithdraw;
        lastWithdrawTime[msg.sender] = now;
    }
 }
