let i, a = 0, b = 0, c = 0, d = 0, e = 0;

for (i = 0; i < 10; i++) {
  a += i;
}

while (b++ < 5) c += b;

while (d++ < 10) {
  if (d < 7) continue;
  e += d;
  break;
}

a === 45 && c === 15 && e === 7;
