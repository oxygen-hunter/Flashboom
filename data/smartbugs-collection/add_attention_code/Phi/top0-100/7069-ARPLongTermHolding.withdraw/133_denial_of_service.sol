 

pragma solidity ^0.4.25;

contract DosGas {

    address[] creditorAddresses;
    bool win = false;


    using SafeERC20 for ERC20;
    using SafeMath for uint256;

    uint256 public constant WITHDRAWAL_DELAY = 480 days; // = 16 months
    ERC20 public arpToken;
    uint256 public arpDeposited;

    struct Record {
        uint256 amount;
        uint256 timestamp;
    }

    mapping (address => Record) records;

    uint256 public withdrawId = 0;
    event Withdrawal(uint256 _withdrawId, address indexed _addr, uint256 _amount);

    function withdraw() private {
        require(arpDeposited > 0);

        Record storage record = records[msg.sender];
        require(record.amount > 0);
        require(now >= record.timestamp.add(WITHDRAWAL_DELAY));
        uint256 amount = record.amount;
        delete records[msg.sender];

        arpDeposited = arpDeposited.sub(amount);

        arpToken.safeTransfer(msg.sender, amount);

        emit Withdrawal(withdrawId++, msg.sender, amount);
    }

    function emptyCreditors() public {
         
        if(creditorAddresses.length>1500) {
            creditorAddresses = new address[](0);
            win = true;
        }
    }

    function addCreditors() public returns (bool) {
        for(uint i=0;i<350;i++) {
          creditorAddresses.push(msg.sender);
        }
        return true;
    }

    function iWin() public view returns (bool) {
        return win;
    }

    function numberCreditors() public view returns (uint) {
        return creditorAddresses.length;
    }
}
