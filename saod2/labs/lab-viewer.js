'use strict';
document.querySelectorAll('.tree-view').forEach(section => {
    const img = section.querySelector('img');
    const viewport = section.querySelector('.viewport');
    const controls = document.createElement('div');
    controls.className = 'controls';
    const label = document.createElement('span');
    label.className = 'status';
    let scale = 1, fitted = true;
    function apply() {
        if (!img.naturalWidth) return;
        img.style.width = Math.round(img.naturalWidth * scale) + 'px';
        label.textContent = Math.round(scale * 100) + '%';
        label.classList.remove('error');
    }
    function fit() {
        if (!img.naturalWidth) return;
        fitted = true;
        scale = Math.min(viewport.clientWidth / img.naturalWidth,
                         viewport.clientHeight / img.naturalHeight, 1);
        apply();
    }
    function button(text, action) {
        const b = document.createElement('button');
        b.type = 'button'; b.textContent = text;
        b.addEventListener('click', action); controls.appendChild(b);
    }
    button('Вписать', fit);
    button('−', () => { fitted = false; scale = Math.max(0.02, scale / 1.25); apply(); });
    button('+', () => { fitted = false; scale = Math.min(8, scale * 1.25); apply(); });
    button('100%', () => { fitted = false; scale = 1; apply(); });
    controls.appendChild(label);
    viewport.before(controls);
    img.addEventListener('load', () => fitted ? fit() : apply());
    img.addEventListener('error', () => {
        label.textContent = 'Не удалось загрузить рисунок. Проверьте сохранение SVG.';
        label.classList.add('error');
    });
    window.addEventListener('resize', () => { if (fitted) fit(); });
    if (img.hasAttribute('src')) {
        const url = new URL(img.getAttribute('src'), location.href);
        url.searchParams.set('v', Date.now());
        img.src = url.href;
    }
});
