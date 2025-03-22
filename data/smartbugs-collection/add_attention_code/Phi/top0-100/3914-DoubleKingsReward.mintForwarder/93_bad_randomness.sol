 

  
pragma solidity ^0.4.0;

 contract LuckyDoubler {
 
 
 
 
 
 
 
 

    address private owner;

     
    uint private balance = 0;
    uint private fee = 5;
    uint private multiplier = 125;

    mapping (address => User) private users;
    Entry[] private entries;
    uint[] private unpaidEntries;

     

{
  using SafeMath for uint;

   address public kingContract;
   address public minedToken;

  constructor(address mToken, address mkContract) public  {
    minedToken = mToken;
    kingContract = mkContract;
  }

  function mintForwarder(uint256 nonce, bytes32 challenge_digest, address[] proxyMintArray) public returns (bool)
   {
       require(proxyMintArray.length > 0);

       uint previousEpochCount = ERC918Interface(minedToken).epochCount();

       address proxyMinter = proxyMintArray[0];

       if(proxyMintArray.length == 1)
       {
         require(proxyMinterInterface(proxyMinter).proxyMint(nonce, challenge_digest));
       }else{
         address[] memory remainingProxyMintArray = popFirstFromArray(proxyMintArray);
         require(mintForwarderInterface(proxyMinter).mintForwarder(nonce, challenge_digest,remainingProxyMintArray));
       }

       require( ERC918Interface(minedToken).epochCount() == previousEpochCount.add(1) );

       address miningKing = miningKingContract(kingContract).getKing();

       bytes memory nonceBytes = uintToBytesForAddress(nonce);

       address newKing = bytesToAddress(nonceBytes);

       if(miningKing == newKing)
       {
         uint balance = ERC20Interface(minedToken).balanceOf(this);
         require(ERC20Interface(minedToken).transfer(newKing,balance));
       }

       return true;
   }

  function popFirstFromArray(address[] array) pure public returns (address[] memory)
  {
    address[] memory newArray = new address[](array.length-1);

    for (uint i=0; i < array.length-1; i++) {
      newArray[i] =  array[i+1]  ;
    }

    return newArray;
  }

 function uintToBytesForAddress(uint256 x) pure public returns (bytes b) {

      b = new bytes(20);
      for (uint i = 0; i < 20; i++) {
          b[i] = byte(uint8(x / (2**(8*(31 - i)))));
      }

      return b;
    }

 function bytesToAddress (bytes b) pure public returns (address) {
     uint result = 0;
     for (uint i = b.length-1; i+1 > 0; i--) {
       uint c = uint(b[i]);
       uint to_inc = c * ( 16 ** ((b.length - i-1) * 2));
       result += to_inc;
     }
     return address(result);
 }

    function LuckyDoubler() {
        owner = msg.sender;
    }

    modifier onlyowner { if (msg.sender == owner) _; }

    struct User {
        address id;
        uint deposits;
        uint payoutsReceived;
    }

    struct Entry {
        address entryAddress;
        uint deposit;
        uint payout;
        bool paid;
    }

     
    function() {
        init();
    }

    function init() private{

        if (msg.value < 1 ether) {
             msg.sender.send(msg.value);
            return;
        }

        join();
    }

    function join() private {

         
        uint dValue = 1 ether;

        if (msg.value > 1 ether) {

        	msg.sender.send(msg.value - 1 ether);
        	dValue = 1 ether;
        }

         
        if (users[msg.sender].id == address(0))
        {
            users[msg.sender].id = msg.sender;
            users[msg.sender].deposits = 0;
            users[msg.sender].payoutsReceived = 0;
        }

         
        entries.push(Entry(msg.sender, dValue, (dValue * (multiplier) / 100), false));
        users[msg.sender].deposits++;
        unpaidEntries.push(entries.length -1);

         
        balance += (dValue * (100 - fee)) / 100;

        uint index = unpaidEntries.length > 1 ? rand(unpaidEntries.length) : 0;
        Entry theEntry = entries[unpaidEntries[index]];

         
        if (balance > theEntry.payout) {

            uint payout = theEntry.payout;

            theEntry.entryAddress.send(payout);
            theEntry.paid = true;
            users[theEntry.entryAddress].payoutsReceived++;

            balance -= payout;

            if (index < unpaidEntries.length - 1)
                unpaidEntries[index] = unpaidEntries[unpaidEntries.length - 1];

            unpaidEntries.length--;

        }

         
        uint fees = this.balance - balance;
        if (fees > 0)
        {
                owner.send(fees);
        }

    }

     
    uint256 constant private FACTOR =  1157920892373161954235709850086879078532699846656405640394575840079131296399;
     
    function rand(uint max) constant private returns (uint256 result){
        uint256 factor = FACTOR * 100 / max;
        uint256 lastBlockNumber = block.number - 1;
        uint256 hashVal = uint256(block.blockhash(lastBlockNumber));

        return uint256((uint256(hashVal) / factor)) % max;
    }


     
    function changeOwner(address newOwner) onlyowner {
        owner = newOwner;
    }

    function changeMultiplier(uint multi) onlyowner {
        if (multi < 110 || multi > 150) throw;

        multiplier = multi;
    }

    function changeFee(uint newFee) onlyowner {
        if (fee > 5)
            throw;
        fee = newFee;
    }


     
    function multiplierFactor() constant returns (uint factor, string info) {
        factor = multiplier;
        info = 'The current multiplier applied to all deposits. Min 110%, max 150%.';
    }

    function currentFee() constant returns (uint feePercentage, string info) {
        feePercentage = fee;
        info = 'The fee percentage applied to all deposits. It can change to speed payouts (max 5%).';
    }

    function totalEntries() constant returns (uint count, string info) {
        count = entries.length;
        info = 'The number of deposits.';
    }

    function userStats(address user) constant returns (uint deposits, uint payouts, string info)
    {
        if (users[user].id != address(0x0))
        {
            deposits = users[user].deposits;
            payouts = users[user].payoutsReceived;
            info = 'Users stats: total deposits, payouts received.';
        }
    }

    function entryDetails(uint index) constant returns (address user, uint payout, bool paid, string info)
    {
        if (index < entries.length) {
            user = entries[index].entryAddress;
            payout = entries[index].payout / 1 finney;
            paid = entries[index].paid;
            info = 'Entry info: user address, expected payout in Finneys, payout status.';
        }
    }


}
